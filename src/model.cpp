
#include "../include/simple_hexapod_controller/model.h"

/***********************************************************************************************************************
 * Initialises leg by calculating leg component lengths and applying forward kinematics for tip position
***********************************************************************************************************************/
void Leg::init(double startYaw, double startLiftAngle, double startKneeAngle)
{
  yaw = startYaw;
  liftAngle = startLiftAngle;
  kneeAngle = startKneeAngle;
  hipLength = hipOffset.norm();
  femurLength = kneeOffset.norm();
  femurAngleOffset = atan2(kneeOffset[2], kneeOffset[0]);
  tibiaLength = tipOffset.norm();
  tibiaAngleOffset = atan2(tipOffset[2], tipOffset[0]);
  minLegLength = sqrt(sqr(tibiaLength) + sqr(femurLength) - 
    2.0*femurLength*tibiaLength*cos(max(0.0, pi-model->minMaxKneeBend[1]))); 
  maxLegLength = sqrt(sqr(tibiaLength) + sqr(femurLength) - 
    2.0*femurLength*tibiaLength*cos(pi-max(0.0, model->minMaxKneeBend[0]))); 
  applyFK(true);
}

/***********************************************************************************************************************
 * Applies inverse kinematics to achieve target tip position
***********************************************************************************************************************/
Vector3d Leg::applyLocalIK(Vector3d tipTarget, bool updateStance)
{
  // application of cosine rule
  Vector3d target = tipTarget;
  target[0] *= mirrorDir;
  target -= rootOffset; // since rootOffset is fixed in root's space
  yaw = atan2(target[1], target[0]);
  Quat quat(Vector3d(0,0,yaw));
  target = quat.inverseRotateVector(target); // localise
  
  target -= hipOffset;
  ASSERT(abs(target[1]) < 0.01);
  target[1] = 0; // any offset here cannot be reached
  double targetLength = target.norm();
  double targetAngleOffset = atan2(target[2], target[0]);
  
  targetLength = clamped(targetLength, minLegLength + 1e-4, maxLegLength - 1e-4); // reachable range
  double lift = acos((sqr(targetLength)+sqr(femurLength)-sqr(tibiaLength))/(2.0*targetLength*femurLength));
  liftAngle = targetAngleOffset + lift;
  double kneeBend = acos(-(sqr(femurLength)+sqr(tibiaLength)-sqr(targetLength))/(2.0*femurLength*tibiaLength));
  kneeAngle = tibiaAngleOffset + kneeBend;
  ASSERT(abs(yaw) < 7.0);
  ASSERT(abs(liftAngle) < 7.0);
  ASSERT(abs(kneeAngle) < 7.0); 
  
  Vector3d resultTipPosition = applyFK(updateStance);
  
  /*
  //Debugging Error Check: Any error occurs due to an imperfect vector rotation algorithm 
  Vector3d diffVec = resultTipPosition - tipTarget;  
  if (diffVec[0] > 1e-3 || diffVec[1] > 1e-3 || diffVec[2] > 1e-3)
    cout << "FORWARD KINEMATICS ERROR: " << diffVec[0] << ":" << diffVec[1] << ":" << diffVec[2] << endl;
  */
  
  Vector3d jointPositions = {yaw, liftAngle, kneeAngle};
  return jointPositions;
}

/***********************************************************************************************************************
 * Applies forward kinematics
***********************************************************************************************************************/
Vector3d Leg::applyFK(bool updateStance)
{
  localTipPosition = calculateFK(yaw, liftAngle, kneeAngle);
  if (updateStance)
    stanceTipPosition = localTipPosition;
  return localTipPosition;
}

/***********************************************************************************************************************
 * Calculates forward kinematics
***********************************************************************************************************************/
Vector3d Leg::calculateFK(double yaw, double liftAngle, double kneeAngle)
{
  Vector3d tipPosition;
  tipPosition = tipOffset;
  tipPosition = Quat(Vector3d(0, kneeAngle, 0)).rotateVector(tipPosition) + kneeOffset;
  tipPosition = Quat(Vector3d(0, -liftAngle, 0)).rotateVector(tipPosition) + hipOffset;
  tipPosition = Quat(Vector3d(0, 0, yaw)).rotateVector(tipPosition) + rootOffset;
  tipPosition[0] *= mirrorDir;
  
  return tipPosition;
}

/***********************************************************************************************************************
 * Defines hexapod model
***********************************************************************************************************************/
Model::Model(Parameters params) : 
  stanceLegYaws(params.stanceLegYaws), 
  yawLimitAroundStance(params.yawLimits), 
  minMaxKneeBend(params.kneeLimits), 
  minMaxHipLift(params.hipLimits), 
  jointMaxAngularSpeeds(params.jointMaxAngularSpeeds)
{
  for (int l = 0; l<3; l++)
  {
    for (int s = 0; s<2; s++)
    {
      Leg &leg = legs[l][s];
      leg.model = this;
      leg.rootOffset = params.rootOffset[l][s];
      leg.hipOffset  = params.hipOffset[l][s];
      leg.kneeOffset = params.kneeOffset[l][s];
      leg.tipOffset  = params.tipOffset[l][s];
      leg.mirrorDir = s ? 1 : -1;
      leg.init(0,0,0);
      leg.state = WALKING;
    }
  }
}

/***********************************************************************************************************************
 * Set individual leg joint angles
***********************************************************************************************************************/
void Model::setLegStartAngles(int side, int leg, const Vector3d &startAngles)
{
  legs[leg][side].init(startAngles[0], startAngles[1], startAngles[2]);
}

/***********************************************************************************************************************
 * Get locally referenced position values for location of joints from pose (root, hip, knee, tip)
***********************************************************************************************************************/
vector<Vector3d> Model::getJointPositions(const Pose &pose)
{
  vector<Vector3d> positions;
  for (int s = 0; s<2; s++)
  {
    for (int l = 0; l<3; l++)
    {
      Leg &leg = legs[l][s];
      Pose transform;
      transform = Pose(leg.rootOffset, Quat(Vector3d(0, 0, leg.yaw)));
      positions.push_back(pose.transformVector(Vector3d(transform.position[0]*leg.mirrorDir, transform.position[1], transform.position[2])));
      transform *= Pose(leg.hipOffset, Quat(Vector3d(0, -leg.liftAngle, 0)));
      positions.push_back(pose.transformVector(Vector3d(transform.position[0]*leg.mirrorDir, transform.position[1], transform.position[2])));
      transform *= Pose(leg.kneeOffset, Quat(Vector3d(0, leg.kneeAngle, 0)));
      positions.push_back(pose.transformVector(Vector3d(transform.position[0]*leg.mirrorDir, transform.position[1], transform.position[2])));
      transform *= Pose(leg.tipOffset, Quat(Vector3d(0, 0, 0)));
      positions.push_back(pose.transformVector(Vector3d(transform.position[0]*leg.mirrorDir, transform.position[1], transform.position[2])));
      ASSERT(positions.back().squaredNorm() < 1000.0);
    }
  }
  return positions;
}

/***********************************************************************************************************************
 * Restrict joint angles to limits
***********************************************************************************************************************/
void Model::clampToLimits()
{
  // clamp angles and alert if a limit has been hit
  for (int l = 0; l<3; l++)
  {
    for (int side = 0; side<2; side++)
    {
      Leg &leg = legs[l][side];
      if (leg.yaw - stanceLegYaws[l] < -yawLimitAroundStance[l])
      {
        leg.yaw = -yawLimitAroundStance[l] + stanceLegYaws[l];
        cout << "leg " << l << " side " << side << " exceeded yaw limit: " << -yawLimitAroundStance[l] + stanceLegYaws[l] << endl;
      }
      else if (leg.yaw - stanceLegYaws[l] > yawLimitAroundStance[l])
      {
        leg.yaw = yawLimitAroundStance[l] + stanceLegYaws[l];
        cout << "leg " << l << " side " << side << " exceeded yaw limit: " << yawLimitAroundStance[l] + stanceLegYaws[l] << endl;
      }
      if (leg.liftAngle < minMaxHipLift[0])
      {
        leg.liftAngle = minMaxHipLift[0];
        cout << "leg " << l << " side " << side << " exceeded hip lift limit: " << minMaxHipLift[0] << endl;
      }
      else if (leg.liftAngle > minMaxHipLift[1])
      {
        leg.liftAngle = minMaxHipLift[1];
        cout << "leg " << l << " side " << side << " exceeded hip lift limit: " << minMaxHipLift[1] << endl;
      }
      if (leg.kneeAngle < minMaxKneeBend[0])
      {
        leg.kneeAngle = minMaxKneeBend[0];
        cout << "leg " << l << " side " << side << " exceeded knee limit: " << minMaxKneeBend[0] << endl;
      }
      else if (leg.kneeAngle > minMaxKneeBend[1])
      {
        leg.kneeAngle = minMaxKneeBend[1];
        cout << "leg " << l << " side " << side << " exceeded knee limit: " << minMaxKneeBend[1] << endl;
      }
    }
  }
}

/***********************************************************************************************************************
***********************************************************************************************************************/


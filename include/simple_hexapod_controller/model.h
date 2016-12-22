#pragma once
#include "standardIncludes.h"
#include "parametersAndStates.h"
#include "quat.h"
#include "pose.h"
#include "walkController.h"
#include <Eigen/src/Core/Matrix.h>
#include <boost/concept_check.hpp>

//extern AutoNavigationParameters params;

// defines the hexapod model
class Model
{
  public:
    Model(Parameters parameters);    
    
    inline std::map<int, *Leg>* getLegContainer(void) { return &leg_container_;};
    inline Leg3DOF* getLegByID(int id) { return leg_container_[id];};
    inline int getLegCount(void) { return leg_count_; };
    inline Pose getCurrentPose(void) { return current_pose_; };
    
    inline void setCurrentPose(Pose pose) { current_pose_ = pose; };
    
    vector<Vector3d> getJointPositions(const Pose &pose);
    void clampToLimits(std::map<int, std::string> leg_name_map);
    void updateLocal(Vector3d target_tip_positions[3][2], double delta_z[3][2]);
    
  private:
    std::map<std::string, *Leg> leg_container_;
    int leg_count_;
    
    Pose current_pose_;  // Current pose of body including all compensation posing
    
    Vector3d stance_coxa_angles_;
    Vector3d coxa_angle_limit_around_stance_;
    Vector2d min_max_tibia_angle_;
    Vector2d min_max_femur_angle_;
    Vector3d joint_max_angular_speeds_;
};

//Base leg class
class Leg
{
  public:
    Leg(int id_number, Parameters params);
    
    inline int getIDNumber(void) { return id_number_; };
    inline std::string getIDName(void) { return id_name_; };
    inline double getMirrorDir(void) { return mirror_dir_;};
    
    inline LegType getType(void) { return leg_type_; };
    inline void setType(LegType leg_type) { leg_type_ = leg_type; };
    
    inline LegState getLegState(void) { return leg_state_; };
    inline void setLegState(LegState leg_state) { leg_state_ = leg_state; };    
    
    inline double getMinLegLength(void) { return min_leg_length_;};
    inline double getMaxLegLength(void) { return max_leg_length_;};
    
    inline Vector3d getWalkedTipPosition(void) { return leg_stepper_->getCurrentTipPosition(); };
    inline Vector3d getPosedTipPosition(void) { return posed_tip_position_; };
    inline Vector3d getLocalTipPosition(void) { return local_tip_position_; };
    
    inline LegStepper* getLegStepper(void) { return leg_stepper_ ;};
    inline void setLegStepper(WalkController* walker, Vector3d identity_tip_position) { leg_stepper_ = new LegStepper(walker, this, identity_tip_position); };
    
    inline LegPoser* getLegPoser(void) { return leg_poser_ ;};
    inline void setLegPoser(PoseController* poser, Vector3d packed_joint_positions, Vector3d unpacked_joint_positions) { leg_poser_ = new LegPoser(poser, this, packed_joint_positions, unpacked_joint_positions); };
    
    Vector3d applyLocalIK(Vector3d tip_target); // sets angles to reach local position relative to root    
    Vector3d applyFK(); // works out local tip position from angles
  
  protected:
    const int id_number_;
    const std::string id_name_;
    
    const LegType leg_type_;
    LegState leg_state_;
    
    std::map<std::string, *Joint> joint_container_;
    std::map<std::string, *Link> link_container_;
    
    LegStepper* leg_stepper_;
    LegPoser* leg_poser_;
    
    Vector3d posed_tip_position_; 
    Vector3d local_tip_position_;  // actual tip position relative to root
    
    const double min_leg_length_;
    const double max_leg_length_;
    
    const double mirror_dir_;  // 1 or -1 for mirrored
    
    struct Model *model_;  // so it can refer to model's joint limits  
};

//3 Degree of freedom leg class
class Leg3DOF: public Leg
{
  public:  
    Leg3DOF(int id_number, Parameters params);
    
    inline int getTripodGroup(void) { return tripod_group_; }
    
    inline LegState getLegState(void) { return leg_state_; };
    inline void setLegState(LegState leg_state) { leg_state_ = leg_state; };
    
    inline double getCoxaJointPosition(void) { return coxa_joint_position_; };
    inline double getFemurJointPosition(void) { return femur_joint_position_; };
    inline double getTibiaJointPosition(void) { return tibia_joint_position_; };
    
    inline double getCoxaLinkLength(void) { return coxa_link_length_;};
    inline double getFemurLinkLength(void) { return femur_link_length_;};
    inline double getTibiaLinkLength(void) { return tibia_link_length_;};
    
    inline Vector3d getCoxaOffset(void) {return coxa_offset_;};
    inline Vector3d getFemurOffset(void) {return femur_offset_;};
    inline Vector3d getTibiaOffset(void) {return tibia_offset_;};
    inline Vector3d getTipOffset(void) { return tip_offset_;};
    
    inline double getDefaultCoxaJointPosition(void) { return default_coxa_joint_position_;};
    inline double getMinCoxaJointLimitAroundDefault(void) { return min_coxa_joint_limit_around_default_;};
    inline double getMaxCoxaJointLimitAroundDefault(void) { return max_coxa_joint_limit_around_default_;};

    void init(double initial_coxa_angle, double initial_femur_angle, double initial_tibia_angle);
    Vector3d calculateFK(double coxa_angle, double femur_angle, double tibia_angle);   
    
  private:    
    int tripod_group_;
    
    double coxa_joint_position_;
    double femur_joint_position_;
    double tibia_joint_position_;

    // these are all local to parent
    Vector3d coxa_offset_;
    Vector3d femur_offset_;
    Vector3d tibia_offset_;
    Vector3d tip_offset_;
    
    double coxa_link_length_;
    double femur_link_length_;    
    double tibia_link_length_;
    
    double femur_angle_offset_;
    double tibia_angle_offset_;    

    double old_coxa_angle_;
    double old_femur_angle;
    double old_tibia_angle_;  
    
    double default_coxa_joint_position_;
    
    double min_coxa_joint_limit_around_default_;
    double max_coxa_joint_limit_around_default_;
    double min_femur_joint_limit_;
    double max_femur_joint_limit_;
    double min_tibia_joint_limit_;
    double max_tibia_joint_limit_;
};

class Joint //TBD
{
  public:
    Joint(int id_number);
  
  private:
    int id_number;
    std::string id_name;
    
    const double position_offset;
    
    double position;
    double velocity;
    
    double last_position;
    double last_velocity; 
};

class Link //TBD
{
  public:
    Link(int id_number);
    
  private:
    const double link_length_;
};





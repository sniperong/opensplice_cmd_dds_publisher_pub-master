#ifndef VELOCITIESDATASPLTYPES_H
#define VELOCITIESDATASPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_VelocitiesData.h"


extern c_metaObject __VelocitiesData_VelocitiesData__load (c_base base);

extern const char *VelocitiesData_Velocities_metaDescriptor[];
extern const int VelocitiesData_Velocities_metaDescriptorArrLength;
extern const int VelocitiesData_Velocities_metaDescriptorLength;
extern c_metaObject __VelocitiesData_Velocities__load (c_base base);
struct _VelocitiesData_Velocities ;
extern  v_copyin_result __VelocitiesData_Velocities__copyIn(c_base base, const struct VelocitiesData::Velocities *from, struct _VelocitiesData_Velocities *to);
extern  void __VelocitiesData_Velocities__copyOut(const void *_from, void *_to);
struct _VelocitiesData_Velocities {
    c_long robot_id;
    c_double linear_velocity_x;
    c_double linear_velocity_y;
    c_double angular_velocity_z;
};

#undef OS_API
#endif

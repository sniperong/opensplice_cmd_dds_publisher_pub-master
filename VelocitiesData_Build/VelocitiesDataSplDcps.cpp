#include "VelocitiesDataSplDcps.h"
#include "ccpp_VelocitiesData.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__VelocitiesData_Velocities__copyIn(
    c_base base,
    const struct ::VelocitiesData::Velocities *from,
    struct _VelocitiesData_Velocities *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->robot_id = (c_long)from->robot_id;
    to->linear_velocity_x = (c_double)from->linear_velocity_x;
    to->linear_velocity_y = (c_double)from->linear_velocity_y;
    to->angular_velocity_z = (c_double)from->angular_velocity_z;
    return result;
}

void
__VelocitiesData_Velocities__copyOut(
    const void *_from,
    void *_to)
{
    const struct _VelocitiesData_Velocities *from = (const struct _VelocitiesData_Velocities *)_from;
    struct ::VelocitiesData::Velocities *to = (struct ::VelocitiesData::Velocities *)_to;
    to->robot_id = (::DDS::Long)from->robot_id;
    to->linear_velocity_x = (::DDS::Double)from->linear_velocity_x;
    to->linear_velocity_y = (::DDS::Double)from->linear_velocity_y;
    to->angular_velocity_z = (::DDS::Double)from->angular_velocity_z;
}


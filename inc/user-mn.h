/****************************************************************************
	[Project] FlexSEA: Flexible & Scalable Electronics Architecture
	[Sub-project] 'flexsea-manage' Mid-level computing, and networking
	Copyright (C) 2016 Dephy, Inc. <http://dephy.com/>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************
	[Lead developper] Jean-Francois (JF) Duval, jfduval at dephy dot com.
	[Origin] Based on Jean-Francois Duval's work at the MIT Media Lab
	Biomechatronics research group <http://biomech.media.mit.edu/>
	[Contributors]
*****************************************************************************
	[This file] user: User Projects & Functions
*****************************************************************************
	[Change log] (Convention: YYYY-MM-DD | author | comment)
	* 2016-09-23 | jfduval | Initial GPL-3.0 release
	*
****************************************************************************/

#include "main.h"

#ifdef BOARD_TYPE_FLEXSEA_MANAGE

#ifndef INC_USER_H
#define INC_USER_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "user-mn-RICNU_Knee_v1.h"
#include "user-mn-MIT_2DoF_Ankle_v1.h"
#include "user-mn-MotorTestBench.h"
#include  "flexsea_global_structs.h"
//Add your project specific user_x.h file here

//****************************************************************************
// Shared variable(s)
//****************************************************************************

//MIT Ankle 2-DoF:
#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)

extern struct ankle2dof_s ankle2dof_left, ankle2dof_right;

#endif	//PROJECT_ANKLE_2DOF

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void init_user(void);
void user_fsm_1(void);
void user_fsm_2(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//List of projects:
#define PROJECT_BAREBONE		0	//Barebone Execute, default option.
#define PROJECT_ANKLE_2DOF		1	//Biomechatronics 2-DOF Ankle
#define PROJECT_RICNU_KNEE		3	//RIC/NU Knee
#define PROJECT_MOTORTB			4
#define PROJECT_DEV				5	//Experimental code - use with care

//List of sub-projects:
#define SUBPROJECT_NONE			0
#define SUBPROJECT_A			1
#define SUBPROJECT_B			2
//(ex.: the 2-DoF ankle has 2 Execute. They both use PROJECT_2DOF_ANKLE, and each
// 		of them has a sub-project for specific configs)

//Step 1) Select active project (from list):
//==========================================

#define ACTIVE_PROJECT			PROJECT_BAREBONE
#define ACTIVE_SUBPROJECT		SUBPROJECT_NONE

//Step 2) Customize the enabled/disabled sub-modules:
//===================================================

//Barebone FlexSEA-Manage project - no external peripherals.
#if(ACTIVE_PROJECT == PROJECT_BAREBONE)

	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	//#define USE_I2C_1			//3V3, IMU & Digital pot
	//#define USE_I2C_2			//3V3, Expansion
	//#define USE_IMU				//Requires USE_I2C_1
	//#define USE_FLASH_MEM		//FLASH memory
	//#define USE_COMM_TEST		//Comm. characterization tool
	//#define USE_UART3			//Expansion UART

	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM1		DISABLED
	#define RUNTIME_FSM2		DISABLED

	//Project specific definitions:
	//...

#endif	//PROJECT_BAREBONE

//RIC/NU Knee
#if(ACTIVE_PROJECT == PROJECT_RICNU_KNEE)

	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	#define USE_I2C_1			//3V3, IMU & Digital pot
	#define USE_I2C_2			//3V3, Expansion
	#define USE_IMU				//Requires USE_I2C_1
	#define USE_BATTBOARD		//Battery Board, requires USE_I2C_1

	//Runtime finite state machine (FSM):
	//Disable both FSM to use manage as a passthru
	#define RUNTIME_FSM1		DISABLED 	// Control
	#define RUNTIME_FSM2		ENABLED 	//
	//FSM2: Communication, we enabled this state machine to send data
	//back to the GUI.  Manage will now control execute, rather than the GUI.

	//Project specific definitions:
	//...

#endif	//PROJECT_RICNU_KNEE

//MIT 2-DoF Ankle
#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)

	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	//#define USE_I2C_1			//3V3, IMU & Digital pot
	//#define USE_I2C_2			//3V3, Expansion
	//#define USE_IMU			//Requires USE_I2C_1

	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM1		ENABLED
	#define RUNTIME_FSM2		ENABLED

	//Project specific definitions:
	//...

#endif	//PROJECT_ANKLE_2DOF

//Dephy's Motor Test Bench
#if(ACTIVE_PROJECT == PROJECT_MOTORTB)

	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	#define USE_I2C_1			//3V3, IMU & Digital pot
	#define USE_I2C_2			//3V3, Expansion
	#define USE_IMU				//Requires USE_I2C_1
	#define USE_BATTBOARD		//Battery Board, requires USE_I2C_1

	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM1		ENABLED
	#define RUNTIME_FSM2		ENABLED

	//Project specific definitions:
	//...

#endif	//PROJECT_MOTORTB

//Experimental/Dev/Use only if you know what you are doing
#if(ACTIVE_PROJECT == PROJECT_DEV)

	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	#define USE_I2C_1			//3V3, IMU & Digital pot
	#define USE_I2C_2			//3V3, Expansion
	#define USE_IMU				//Requires USE_I2C_1
	#define USE_BATTBOARD		//Battery Board, requires USE_I2C_1
	#define USE_FLASH_MEM		//FLASH memory

	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM1		DISABLED
	#define RUNTIME_FSM2		DISABLED

	//Project specific definitions:
	//...

#endif	//PROJECT_BAREBONE

//****************************************************************************
// Structure(s)
//****************************************************************************

struct ankle2dof_s
{
	uint8_t r_w;					//Read/write values
	uint8_t ctrl;					//Controller
	uint8_t ctrl_change;			//KEEP or CHANGE
	uint8_t ctrl_o;					//Open speed
	uint8_t ctrl_i;					//Current
	struct gains_s ctrl_i_gains;	//Current controller gains
};

#endif	//INC_USER_H

#endif //BOARD_TYPE_FLEXSEA_MANAGE

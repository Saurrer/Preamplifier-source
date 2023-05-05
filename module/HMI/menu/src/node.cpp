/** @file node.cpp
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		May 4, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of node.cpp.
*
* @page node.cpp
* @details Detail description of node.cpp.
*
*/
/* Includes ----------------------------------------------------------------------*/
#include "../inc/node.h"
/* Private typedef ---------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------*/
#define NULL (0U)
#define NODE_INIT_NAME		"NONE"
#define NODE_NAME_OK		(0)
#define NODE_OK			(0U)
#define NODE_FAIL		(1U)
#define NODE_FUNCTION_FAIL	NODE_FAIL

/* Private macro -----------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
/*
  Function:
  Input Data:
  Action:
*/

/* Private functions -------------------------------------------------------------*/

HMI::node_t::node_t()
:pName{NODE_INIT_NAME},
 pNext(NULL),
 pPrevious(NULL),
 pParent(NULL),
 pChild(NULL),
 function(NULL)
{

}

void
HMI::node_t::init(char * name,
		  NODE * next_address, NODE * prev_address,
		  NODE * parent_address, NODE * child_address,
		  void (*function_address)(void))
{
  pName = name;
  pNext = next_address;
  pPrevious = prev_address;
  pParent = parent_address;
  pChild = child_address;
  function = function_address;
}


/*-------------------------------END OF FILE--------------------------------------*/

/** @file node.h
*
* @author 		
* Mariusz Mikulski	\n
* Company: 	\n
* Departament:	\n
* @date		Mar 2, 2023
* @version 	1.0.0
* @copyright 	© 2023. All Rights Reserved.
*
* @brief brief description of node.h.
*
* @page node.h
* @details Detail description of node.h.
*
*/

/* Define to prevent recursive inclusion -----------------------------------------*/
#ifndef _NODE_H_
#define _NODE_H_

/* Includes ----------------------------------------------------------------------*/
#include <stdint.h>

/* Exported define ---------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------*/

/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Exported Object types ---------------------------------------------------------*/

namespace HMI
{
  typedef class node_t NODE;

  class node_t
  {
  public:
    node_t();
    void init(char * name, NODE * next_address, NODE * prev_address,
		      NODE * parent_address, NODE * child_address,
		      void (*function_address)(void));

    char * pName;	/**< node name */

    NODE * pNext;
    NODE * pPrevious;
    NODE * pParent;
    NODE * pChild;

    void(*function)(void);

  private:

  };

}

/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/

#endif /* _NODE_H_ */

/*-------------------------------END OF FILE--------------------------------------*/

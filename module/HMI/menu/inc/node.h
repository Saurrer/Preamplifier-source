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

/* Exported define ---------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------*/
typedef struct node_t NODE;

/* Exported constants ------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------- */
/**
* @brief Brief description of function
*/

/* Exported Object types ---------------------------------------------------------*/
struct node_t
{

  const char * Name;		/**< node name */

  NODE * pNext;
  NODE * pPrevious;
  NODE * pParent;
  NODE * pChild;

  void(*function)(void);

};
/* Exported Object constants -----------------------------------------------------*/
/* Exported Object macro ---------------------------------------------------------*/
/* Exported Object functions -----------------------------------------------------*/

#endif /* _NODE_H_ */

/*-------------------------------END OF FILE--------------------------------------*/

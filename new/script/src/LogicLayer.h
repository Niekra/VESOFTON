/** @file LogicLayer.h
 *  @brief Function prototypes for the logiclayer.
 *
 *  The Logiclayer gets the input from the Userinterface.
 *  The input gets saved inside a command struct and then executed.
 *
 *  Uses: TIM5
 *
 *  @author Matthijs Daggelders
 *  @author Niek Ratering Arntz
 *  @bug Wait time isnt't correctly waiting the first time.
 */

#ifndef LOGICLAYER_H_
#define LOGICLAYER_H_

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <Vgascreen.h>
#include<InputOutput.h>
#include "stm32f4xx.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include<InputOutput.h>



//--------------------------------------------------------------
// Namespace LL
//--------------------------------------------------------------
/** @brief Namespace LL
 *
 * 	In the namespace LL are all the functions concerning the LogicLayer.
 *
 */
namespace LL {

//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
/** @defgroup LL defines
 *  Group of LL global defines.
 *  @{
 */

/** @brief Amount of colors. */
#define COLORS 16

/** @brief Prescaler for the wait timer. */
#define TIM5_PRESCALE 2000

/** @brief Time period for the wait timer.
 *
 * 	TIM5
 * 	basefreq = 2*APB1 (APB1=42MHz) => TIM_CLK=84MHz
 * 	84Mhz/84000/1 = 1kHz
 * 	84Mhz = 84 MHz /x/ 84000   => x =  ms
 *
 *  */
#define TIM5_PERIOD 84000

/** @brief Repetition counter for TIM5 */
#define TIM5_REP 1

/** @brief NVIC priority value. */
#define LOW_PRIORITY 0

/** @brief Amount of commando's that can be buffered. */
#define MAX_BUFFERS 120

/** @brief Maximum string length for command types and colors. */
#define MAX_COLOR_LENGTH 15

/** @brief Maximum string length for an int. */
#define MAX_INT_LENGTH 6

/** @brief Maximum text length. */
#define MAX_TEXT_LENGTH 64

/** @brief Maximum fill length */
#define MAX_FILL_LENGTH 4
/** @} */ // end of LL defines

//--------------------------------------------------------------
// LogicLayer structs
//--------------------------------------------------------------
/**
 * @brief Struct command_t for saving incoming commands.
 *
 * The command_t struct has 8 char arrays of different sizes.
 * Different sizes are used to limit RAM usage.
 */
typedef struct {
	char type[MAX_COLOR_LENGTH];	/**< The type of command. */
	char input1[MAX_COLOR_LENGTH];	/**< First input of the command. */
	char input2[MAX_INT_LENGTH];	/**< Second input of the command. */
	char input3[MAX_TEXT_LENGTH];	/**< Third input of the command, this one is the largest for text. */
	char input4[MAX_COLOR_LENGTH];	/**< Fourth input of the command. */
	char input5[MAX_COLOR_LENGTH];	/**< Fifth input of the command. */
	char input6[MAX_COLOR_LENGTH];	/**< Sixth input of the command.. */
	char input7[MAX_COLOR_LENGTH];	/**< Seventh input of the command. */
	char input8[MAX_FILL_LENGTH];	/**< eighth input of the command. */
}command_t;

/**
 * @brief Logic_t struct for the different flags and buffer.
 *
 * The logic_t structs saves the different flags of the Logiclayer.
 * The struct also saves the commands in a buffer.
 */
typedef struct{
	Vgascreen screen;					/**< The Vgascreen object. */
	volatile int waiting;				/**< The waiting FLAG. */
	volatile int bufferIndex;			/**< Integer for the current command. */
	volatile int bufferCnt;				/**< Amount of commands buffered. */
	command_t buffers[MAX_BUFFERS];		/**< Buffer for the commands. */
}logic_t;


//--------------------------------------------------------------
// Global functions
//--------------------------------------------------------------
/** @brief (GLOBAL)Initiate the LogicLevel.
 *
 *	Initiates the LogicLevel. All the flags are reset and a Vgascreen object is created.
 *	Everything is saved in the logic struct.
 *
 *  @param void
 *  @return int error
 */
int init_LL();

/** @brief (GLOBAL)executes the last command or the command buffer.
 *
 * 	If the wait flag isnt set execute the command given by the bufferIndex.
 * 	While there are still commands in the command buffer keep executing them.
 *
 * 	if the waiting flag is set return.
 *
 *  @param void
 *  @return int error
 */
int exec();

/** @brief (GLOBAL)Destroy the LogicLayer
 *
 *	Deletes and Vgascreen object and resets all the flags.
 *
 *  @param void
 *  @return int error
 */
int delete_LL();

/** @brief (GLOBAL)Sets the command struct.
 *
 *	Turns the input buffer into a command. It uses strtok_r to split the input at every ",".
 *
 *  @param char *buf the char buffer to set
 *  @return int error
 */
int set_Command(char *buf);


// The interrupt handlers are in C.
#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------
// Global functions(C) and interrupt handler for TIM5
//--------------------------------------------------------------
/** @brief (GLOBAL) TIM5_IRQh for wait_Ms
*
*	The TIM5_IRQh interrupts when the timer is triggered.
*	The interrupt stops the read function of the IO::level to exec() the buffer.
*	The waiting FLAG is also cleared.
*	Directly calling the exec() function messes with the VGA output.
*
 *  @param void
 *  @return void
*/
void TIM5_IRQHandler(void);

// C functions uses TIM5.
/** @brief (LOCAL)The wait function of the LogicLevel
 *
 *	the function enables TIM5 and sets the prescale to give an interrupt at the chosen time.
 *	The waiting FLAG is also set, so no further commands will be executed.
 *
 *  @param int ms, the time to wait
 *  @return int error
 */
int wait_Ms(int ms);

/** @brief (LOCAL)Initiate TIM5 for the wait_Ms function.
 *
 * 	Sets the TIM5 and NVIC settings for interrupts on TIM5.
 *
 *  @param void
 *  @return int error
 */
int init_TIM5();

#ifdef __cplusplus
}
#endif



} /* namespace LL */

#endif /* LOGICLEVEL_H_ */


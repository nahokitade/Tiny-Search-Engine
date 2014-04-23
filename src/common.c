/* Component name: Crawler
 *
 * Author: Naho Kitade
 * Date: April 2014
 *
 * You should include in this file your functionality for the hashtable as
 * described in the assignment and lecture.
 */
/* ========================================================================== */

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen

// ---------------- Local includes  e.g., "file.h"

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes
//
// Deletes web page but keeps url intact for Hash table.
int deleteWebPage(WebPage *toDeleteWeb){
	free(toDeleteWeb->html);
	free(toDeleteWeb);
	return 1;
}




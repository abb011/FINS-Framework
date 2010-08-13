/*
 * icmp_receive.c
 *
 *  Created on: Aug 3, 2010
 *      Author: alex
 */

#include "icmp.h"

void icmp_receive(struct finsFrame* ff) {

	if (ff->dataOrCtrl == DATA) {
		if (ff->dataFrame.directionFlag == UP) {
			switch (ff);
		}
		else {
			// need to deal with constructing packets and knowing which one to construct.
		}
	}
	else {
		// to do deal with FCF
	}
}

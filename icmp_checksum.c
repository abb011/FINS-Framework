/**
 * icmp_checksum.c
 *
 *  Created on: Aug 13, 2010
 *      Author: alex
 */


/**
 * Attempts to be a universal checksum for all ICMP messages.
 */
unsigned short icmp_checksum(struct icmp_packet packet, int length,
		int minLength) {

	unsigned short* ptr;
	int sum;
	sum = 0;
	unsigned short checkreturn;

	if (length % 2) {
		packet.echo.data[length - minLength] = 0; 		/* pads the data if the length is an odd number*/
		length += 1;
	}
	ptr = &packet;										/* sets the pointer to the begining of the packet */
	length = length / 2; 								/* divide by two because we are taking 2 bytes at a time */
	for (int length; length > 0; length--) {
		sum += *ptr++;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16); 								/* sum is now the complete addition but still needs to be turned into a short and complimented */

	checkreturn = (unsigned short) (~ucksum & 0xffff);
	return checkreturn;

}

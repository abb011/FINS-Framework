/*
 * ICMP.h
 *
 *  Created on: Jul 21, 2010
 *      Author: alex
 */

#ifndef ICMP_H_
#define ICMP_H_

/*Type value for an ICMP Error message*/

#define ERROR_UNREACHABLE			 	3			/* the destination is unreachable */
#define ERROR_QUENCH 					4			/* source quench (received too many packets) */
#define ERROR_TIME 						11			/* Time to Live reached 0 before reaching destination */
#define ERROR_PARAM 					12			/* Ambiguous or missing value in any field in the datagram */
#define ERROR_REDIRECT 					5			/* When host sends the data to the wrong router. Results in a routing table update for the host */

/* Type value for ICMP Query messages */
#define QUERY_ECHO_REQUEST				0			/* request for echo */
#define QUERY_ECHO_REPLY				8			/* reply to echo*/
#define QUERY_TIMESTAMP_REQUEST			13			/* time stamp request  determines roundtrip of an IP packet */
#define QUERY_TIMESTAMP_REPLY			14			/* time stamp reply */
#define QUERY_ADDR_REQUEST				17			/* request to router on LAN if known address or broadcast to all for the address mask*/
#define	QUERY_ADDR_REPLY				18			/* reply with address mask */
#define	QUERY_ROUTER_REQUEST			10			/* request for router address and if its alive. Multicast / Broadcast */
#define	QUERY_ROUTER_REPLY				9			/* reply with address and if its alive*/

/* code values for destination unreachable */
#define NETWORK_UNR						0			/* The datagram could not reach the specified network */
#define HOST_UNR						1			/* The datagram could not reach the specified host inside of the network*/
#define PROTOCOL_UNR					2			/* Unreachable or invalid protocol number of the host */
#define PORT_UNR						3			/* Invalid port*/
#define FRAGMENTATION_NEEDED			4			/* The packet is of size that needs to be fragmented but the "Do Not Fragment" flag is set*/
#define	SOURCE_ROUTE_FAILED				5			/* Router could not forward the datagram to the next step */
#define	DEST_NETWORK_UNK				6			/* Destination Network Unknown is not used, code 0 is used instead */
#define	DEST_HOST_UNK					7			/* The specified host is not known. ie bad address */
#define SRC_HOST_ISOLATED				8			/* Source Host Isolated is no longer used */
#define	DST_NTWRK_PROHIB				9			/* The source device is not allowed to send data to the network of the destination */
#define	DST_HOST_PROHIB					10			/* The source is allowed to send to the network of the target device, but not to the target device */
#define	DST_NTWRK_SRVC_UNR				11			/* The network specified in the IP address cannot be reached because the service specified in the "Type Of Service" field is unreachable */
#define DST_HOST_SRC_UNR				12			/* The destination specified in the IP address cannot be reached because the service specified in the "Type Of Service" field is unreachable */
#define	COMMUNICATION_PROHIB			13			/* The datagram could not be forwarded due to filtering that blocks messages based on their contents */
#define HOST_PRECED_VIOLATION			14			/* Sent by first-hop router when the precedence value in the "Type of Service" field is not allowed */
#define PRECED_CUTOFF					15			/* Sent by router when the precedence value is lower than the minimum allowed on the network at that point in time */


/* Time exceeded code Values */
#define EXPIRATION  					0			/* The time to live of field has expired*/
#define REASSEMBLY						1			/* The fragment reassembly time has been exceeded */


/* Redirect Code values code 0 and 2 were prohibited by RFC 1812.*/
#define REDIR_NETWORK					0			/* [obsolete] Redirect all future datagrams sent on this network to this device  */
#define REDIR_HOST						1			/* Redirect all future datagrams going to the device/address that caused the ICMP error */
#define REDIR_TOS_NTWRK					2			/*  [obsolete] Forward all future datagrams with the same Type of Service value on the entire network */
#define REDIR_TOS_HOST					3			/* Redirect all future datagrams with the same Type of Service */


/* Parameter Problem code values */
#define POINTER_IND						0			/* The pointer is pointing to the location of the error */
#define MISSING_REQ						1			/* The IP datagram is missing a required option. The point can't point to nothing */
#define BAD_LEN							2			/* The length of the datagram was incorrect */

/* Router Advertise and solicitation codes*/
#define NORMAL							0			/* normally the field is set to 0 with some exceptions */
#define MOBILE_AGENT					16			/* When a Mobile IP agent is sending the Router Advertisement it may set the value 16 if the receiving device is also a mobile agent that doesn't intend to handle normal trafic. */

#define UNUSED							0			/* The code field is not used by Source Quench, Echo, Timestamp, Router solicitation */

#define MAX_ICMP_LEN				548			/* 576 bytes total max - 4 bytes for ICMP header -4 for unused - 20 IP header*/



struct ip4_header{

	uint8_t ip_verlen;						 		/* IP version & header length (in longs)*/
	uint8_t ip_dif; 								/* differentiated service			*/
	uint16_t ip_len; 								/* total packet length (in octets)	*/
	uint16_t ip_id; 								/* datagram id				*/
	uint16_t ip_fragoff; 							/* fragment offset (in 8-octet's)	*/
	uint8_t ip_ttl; 								/* time to live, in gateway hops	*/
	uint8_t ip_proto; 								/* IP protocol */
	uint16_t ip_cksum; 								/* header checksum 			*/
	uint32_t ip_src;		 						/* IP address of source			*/
	uint32_t ip_dst; 								/* IP address of destination		*/
};


/* used by Destination Unreachable, Source Quench, Time Exceeded*/
struct error_message{
	uint32_t unused;								/* 4 bytes of unused data */
	struct ip4_header;								/* original IP header of the original IP datagram */
	unsigned char data[MAX_ICMP_LEN];				/* RFC 1812 says that an ICMP error message should contain as much of the original data as possible without exceeding a total length of 576 bytes*/

};
/* used by parameter problems */
struct error_param{
	uint8_t pointer;								/* pointer to the byte that caused the Parameter Problem message to be generated */
	uint24_t unused;								/* 3 bytes of unused data*/
	struct ip4_header;								/* original IP header of the original IP datagram */
	unsigned char data[MAX_ICMP_LEN];
};
struct error_redir{
	uint32_t preferedRouter;						/* The IP address of the preferred router for future transmissions. */
	struct ip4_header;								/* original IP header of the original IP datagram */
	unsigned char data[MAX_ICMP_LEN];
};


struct info_echo{
	uint16_t identifier;							/* Helps sort multiple Echo requests. Originally intended for a "higher level label" like a session identifier. However it used differently by different implementations. Sometimes filled with process number */
	uint16_t sequence;								/* Originally for identifying messages in a series.  Once again up to implementation for how to use */
	unsigned char data[MAX_ICMP_LEN]				/* Optional data, unspecified*/
};

struct info_timestamp{
	uint16_t identifier;							/* Helps sort multiple Echo requests. Originally intended for a "higher level label" like a session identifier. However it used differently by different implementations. Sometimes filled with process number */
	uint16_t sequence;								/* Originally for identifying messages in a series.  Once again up to implementation for how to use */
	uint32_t originate;								/* Time the original was sent time in MS after midnight*/
	uint32_t receive;								/* Time the original was received*/
	uint32_t transmit;								/* Time the reply was sent*/

};


struct info_router_adv{
	uint8_t	numAddrs;								/* the number of address's associated with the router that are in the data */
	uint8_t	addrSize;								/* number of 32 bit words associated with each address. It should be fixed at two [Router Address and Preference Level] */
	uint16_t lifetime;								/* The number of seconds the host should consider the information as valid. */
	uint32_t data[MAX_ICMP_LEN/4]					/* 32 bit address then 32 bit preference level. This repeats the amount of times in the Number of Address field */
};  /* The preference field is used for multiple addresses. The higher the number the more routers prefers to receive datagrams on. */


struct info_router_sol{
	uint32_t reserved;								/* 4 bytes that should all be set to 0 */
};

struct icmp_packet{
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	union{
		struct error_message;
		struct error_redir;
		struct error_param;
		struct info_echo;
		struct info_timestamp;
		struct info_router_adv;
		struct info_router_sol;
	};

};


#endif

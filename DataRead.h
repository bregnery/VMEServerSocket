#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "CAENVMElib.h" 
#include "CAENVMEtypes.h"


/*
 * This is a Set of Functions that reads data recieved from the client and returns the status to the Server
 *
 * sockfd is the socket number
 */

int32_t info[2];

int32_t ReadCAENVME_Init(int32_t storage[6], int32_t sockfd){
	//printf("Parameter Values: \n");
	/*
	int32_t i;
	for(i=0; i<6; i++){
		printf("%d\n", storage[i]);
	}
	*/
	int32_t n, status;
	status = CAENVME_Init((CVBoardTypes)storage[1],(short)storage[2],(short)storage[3],&storage[4]);
	info[0] = status;
	info[1] = storage[4];
	n = write(sockfd, info, sizeof(info));
	return n;
}

int32_t ReadCAENVME_End(int32_t storage[6], int32_t sockfd){
	//printf("Parameter Value: %d\n", storage[1]);
	int32_t n, status;
	status = CAENVME_End(storage[1]);
	info[0] = status;
	info[1] = storage[1];
	n = write(sockfd, info, sizeof(info));
	return n;
}

int32_t ReadCAENVME_WriteCycle(int32_t storage[6], int32_t sockfd){
	//printf("Parameter Values: \n");
	/*
	int32_t i;
	for(i=0; i<6; i++){
		printf("%d\n", storage[i]);
	}
	printf("Parameters Printed \n");
	*/
	int32_t n, status;
	status = CAENVME_WriteCycle(storage[1],(uint32_t)storage[2],(void*)&storage[3],(CVAddressModifier)storage[4],(CVDataWidth)storage[5]);
	info[0] = status;
	info[1] = storage[3];
	n = write(sockfd, info, sizeof(info));
	return n;
}

int32_t ReadCAENVME_ReadCycle(int32_t storage[6], int32_t sockfd){
	//printf("Parameter Values: \n");
	/*
	int32_t i;
	for(i=0; i<6; i++){
		printf("%d\n", storage[i]);
	}
	*/
	int32_t n, status;
	status = CAENVME_ReadCycle(storage[1],(uint32_t)storage[2],(void*)&storage[3],(CVAddressModifier)storage[4],(CVDataWidth)storage[5]);
	info[0] = status;
	info[1] = storage[3];
	n = write(sockfd, info, sizeof(info));
	return n;
}

/*
int32_t CAENVME_Init(CVBoardTypes BdType, short Link, short BdNum, int32_t *Handle){
	printf("%d\n", BdType);
	printf("%d\n", Link);
	printf("%d\n", BdNum);
	printf("%d\n", *Handle);
	return cvSuccess;
}


int32_t CAENVME_End(int32_t Handle){
	printf("%d\n", Handle);
	return cvSuccess;
}

int32_t CAENVME_WriteCycle(int32_t Handle, uint32_t Address, void *Data, CVAddressModifier AM, CVDataWidth DW){
	printf("%d\n", Handle);
	printf("%d\n", Address);
	printf("%d\n", *((uint32_t*)Data));
	printf("%d\n", AM);
	printf("%d\n", DW);
	return cvSuccess;
}

int32_t CAENVME_ReadCycle(int32_t Handle, uint32_t Address, void *Data, CVAddressModifier AM, CVDataWidth DW){	
	printf("%d\n", Handle);
	printf("%d\n", Address);
	printf("%d\n", *((uint32_t*)Data));
	printf("%d\n", AM);
	printf("%d\n", DW);
	return cvSuccess;
}
*/

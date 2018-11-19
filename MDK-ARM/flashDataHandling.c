#include "stm32f3xx_hal.h"
#include "flash_api.h"


#define dataStartAddressD  (ADDR_FLASH_PAGE_30)


uint8_t eraseError=0;
uint8_t writeError=0;
uint32_t PageError=0;

static FLASH_EraseInitTypeDef EraseInitStruct;

void flashErase(void){

  
	 /* Fill EraseInit structure*/
 /* Fill EraseInit structure*/
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.PageAddress = ADDR_FLASH_PAGE_30;
  EraseInitStruct.NbPages     = 1; //cau
	
	
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK){eraseError=1;}
	
}


void flashWriteF(uint32_t Address, float* data, uint8_t N ){

	uint8_t i;
	
	for(i=0;i<N;i++){
	
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, *(uint32_t *)(&data[i])) != HAL_OK){writeError=1;}
		
		Address=Address+4;
	
	}


}


void flashWriteD(uint32_t Address, uint32_t* data, uint8_t N ){

	uint8_t i;
	
	for(i=0;i<N;i++){
	
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, *(uint32_t *)(&data[i])) != HAL_OK){writeError=1;}
		Address=Address+4;
		
	}

}


void flashReadF(uint32_t Address, float* data, uint8_t N ){

	uint8_t i;
	
	for(i=0;i<N;i++){
	
		data[i]=*(float *)(Address);
		Address+=4;
			
	}

}


void flashReadD(uint32_t Address, uint32_t* data, uint8_t N ){

	uint8_t i;
	
	for(i=0;i<N;i++){
	
		data[i]=*(uint32_t *)(Address);
		Address+=4;
			
	}

}


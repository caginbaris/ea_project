#include "stm32f3xx_hal.h"
#include "menu_definitions.h"
#include "flash_api.h"


#define sentinelAdress     (ADDR_FLASH_PAGE_30)
#define dataStartAddress  (sentinelAdress+4)

#define sentinelValue 0xA1B2C3D4

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





void flashWriteD(uint32_t Address, uint32_t* data, uint8_t N ){

	uint8_t i;
	
	for(i=0;i<N;i++){
	
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, *(uint32_t *)(&data[i])) != HAL_OK){writeError=1;}
		Address=Address+4;
		
	}

}





void flashReadD(uint32_t Address, uint32_t* data, uint8_t N ){

	uint8_t i;
	
	for(i=0;i<N;i++){
	
		data[i]=*(uint32_t *)(Address);
		Address+=4;
			
	}

}


void flashRead(void){
	
	uint32_t sentinel;
	
	flashReadD(sentinelAdress,&sentinel,1);
	
	if(sentinel==sentinelValue){
	
	flashReadD(dataStartAddress,flash.uBuffer,flashWordSize);
	
	}		
	
}


void flashWrite(void){
	
	static uint8_t flashWriteCheck=1;
	uint32_t sentinel=0xA1B2C3D4;
	
	
	if(flashWriteCheck){
		
		//crc calculation can be added
		
	__disable_irq();
	
		HAL_FLASH_Unlock();
	
		flashErase();

		if(eraseError==0){
	
		flashWriteD(sentinelAdress,&sentinel,1);	
		flashWriteD(dataStartAddress,flash.uBuffer,flashWordSize);
		
		}
	
		HAL_FLASH_Lock();
	
		__enable_irq();
		
		}
	
		flashWriteCheck=0;
	
}


void init_flashBackRead(){


	flashNew=flash;
	
	
}





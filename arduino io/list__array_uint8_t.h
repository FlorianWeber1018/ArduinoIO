/*
 * list__array_uint8_t.h
 *
 * Created: 15.10.2017 21:43:36
 *  Author: Flo
 */ 


#ifndef LIST__ARRAY_UINT8_T_H_
#define LIST__ARRAY_UINT8_T_H_
#include <stdlib.h>
#include <stdint.h>
#ifndef nullptr
#define nullptr NULL
#endif

class list_array_uint8_t_element 
{
	public:
		list_array_uint8_t_element(list_array_uint8_t_element* pre, uint8_t* data, uint8_t data_size);
		list_array_uint8_t_element(uint8_t* data, uint8_t data_size);
		list_array_uint8_t_element();
		~list_array_uint8_t_element();
		void assign_post(list_array_uint8_t_element* post);
		uint8_t* data;
		uint8_t data_size;
		list_array_uint8_t_element* pre;
		list_array_uint8_t_element* post;
	private:
		

};




#endif /* LIST__ARRAY_UINT8_T_H_ */
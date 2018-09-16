/*
 * list__array_uint8_t.cpp
 *
 * Created: 15.10.2017 21:43:13
 *  Author: Flo
 */
 #include "list__array_uint8_t.h"
list_array_uint8_t_element::list_array_uint8_t_element(list_array_uint8_t_element* pre, uint8_t* data, uint8_t data_size){
	post=nullptr;
	this->pre = pre;
	if(pre!=nullptr){
		pre->assign_post(this);
	}
	
	this->data = (uint8_t*) malloc(data_size);
	for (uint8_t i=0; i<data_size; i++)
	{
		this->data[i]=data[i];
	}
	this->data_size=data_size;
}
list_array_uint8_t_element::list_array_uint8_t_element(uint8_t* data, uint8_t data_size){
	post=nullptr;
	this->pre= nullptr;
	this->data = (uint8_t*) malloc(data_size);
	for (uint8_t i=0; i<data_size; i++)
	{
		this->data[i]=data[i];
	}
	this->data_size=data_size;
}
list_array_uint8_t_element::list_array_uint8_t_element(){
this->pre= nullptr;
this->post=nullptr;
this->data=nullptr;
this->data_size=0;
}
list_array_uint8_t_element::~list_array_uint8_t_element(){
	free(data);
	data=nullptr;
	if(post!=nullptr){
		delete post;
	}
}
void list_array_uint8_t_element::assign_post(list_array_uint8_t_element* post){
	this->post=post;
}
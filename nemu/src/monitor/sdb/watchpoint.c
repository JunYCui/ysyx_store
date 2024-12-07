/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "sdb.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() 
{
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }
  
  head = NULL;
  free_ = wp_pool;//空闲指针指向池
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp()
{
  WP* wpnew;
  WP* temp;
  if(free_ == NULL)
  {
    printf("all watchpoints are used!");
    assert(0);
  }
  else 
  {
    wpnew = free_;
    free_ = free_->next;  
    wpnew->next = NULL;
  }
  
  if(head == NULL)
  {
    head = wpnew;  
    head->next = NULL;
  }
  else 
  {
    temp = head;
    while(temp->next != NULL)
      temp = temp->next;
    temp->next = wpnew;
  }
  return wpnew;

}

void free_wp(int NO)
{
  WP* temp1 = head;
  WP* wp;
  if(head == NULL)
  {
    printf("no working watchpoints\n");
    assert(0);
  }
  while(temp1->NO != NO && temp1->next != NULL)
  {
    temp1 = temp1->next;
  }
  if(temp1->NO == NO)
  {
    wp = temp1;
  }
  else 
  {
    printf("no %d watchpoints \n",NO);
    assert(0);
  }
  //delete from work
  if(head->NO == wp->NO)
  {
    head= wp->next;
  }
  else 
  {
  temp1 = head;
  while(temp1->next->NO != wp->NO)
  {
    temp1 = temp1->next;
  }
    temp1->next = wp->next;
  }
  
  //insert to free
  WP* temp = free_;
  if(wp->NO < free_->NO)
  { 
    wp->next = free_;
    free_ = wp;
  }
  else 
  {
  while(temp->next != NULL)
  {
    if(temp->NO<wp->NO && temp->next->NO>wp->NO)  
    {
      wp->next = temp->next;
      temp->next = wp;
      break;
    }
    temp = temp->next;
  }
  if(temp->next ==NULL)
  {
    temp->next = wp;
    wp->next = NULL;
  }
  }
}

void Wp_info_w(void)
{
  WP*temp;
  if(head == NULL)
  {
    printf("no watchpoints \n");
  }
  temp = head;
  while(temp !=  NULL)
  {
    printf("%d Hw watchpoint:%s\n",temp->NO,temp->exp);
    temp = temp->next;
  }


}

void Wp_info_f(void)
{
  WP*temp;
  if(free_ == NULL)
  {
    printf("no free watchpoints \n");
  }
  temp = free_;
    while(temp !=  NULL)
  {
    printf("watchpoint %d is free \n",temp->NO);
    temp = temp->next;
  }
}
void Cpu_Wp(void)
{
  uint32_t val;
  uint8_t count=0,i=0;
  uint8_t record_No[NR_WP];
  uint32_t record_val[NR_WP][2];
  bool success;
  WP* temp =head;
  while(temp!= NULL)
  {
    val =expr(temp->exp,&success);
    assert(success == true);
    if(val != temp->value)
    {
      record_No[count] = temp->NO;
      record_val[count][0]= temp->value;
      record_val[count][1]= val;
      count++;
      temp->value = val;
    }
    temp = temp->next;
  }
  if(count > 0)
  {
    for(i=0;i<count;i++)
    {
    printf("watchpoint %d value has been changed \n",record_No[i]);
    printf("Old Value:%u \n",record_val[i][0]);
    printf("New Value:%u \n",record_val[i][1]);
    }
    nemu_state.state = NEMU_STOP;
  }
}




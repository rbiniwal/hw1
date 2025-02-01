#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val){
  if(tail_ == NULL){
    Item *temp = new Item();
    tail_ = temp;
    head_ = tail_;
  }
  else if((tail_->last == ARRSIZE)){
    Item *temp = new Item();
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
  }
  tail_->val[tail_->last] = val;
  tail_->last++;
  size_++;
}

void ULListStr::pop_back(){
  if(head_ == NULL || tail_ == NULL){
    return;
  }
  else if(head_->last == 1){
    Item *temp = tail_;
    delete temp;
    head_ = NULL;
    tail_ = NULL;
    size_--;
  }
  else if(tail_->last == 1){
    Item *temp = tail_;
    tail_->val[tail_->last - 1] = '\0';
    tail_ = tail_->prev;
    delete temp;
    size_--;
  }else{
    tail_->val[tail_->last - 1] = '\0';
    tail_->last--;
    size_--;
  }
}

void ULListStr::push_front(const std::string& val){
  if (head_ == NULL){
    Item *temp = new Item();
    head_ = temp;
    head_->first = 1;
    head_->last = 1;
    tail_ = head_;
  }
  else if(head_->first == 0){
    Item *temp = new Item();
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
    head_->first = ARRSIZE;
    head_->last = ARRSIZE;
  }
  head_->val[head_->first - 1] = val;
  head_->first--;
  size_++;
}

void ULListStr::pop_front(){
  if(tail_ == NULL){
    return;
  }
  else if(tail_->first == ARRSIZE - 1){
    Item *temp = head_;
    delete temp;
    head_ = NULL;
    tail_ = NULL;
    size_--;
  }
  else if(head_->first == ARRSIZE - 1){
    Item *temp = head_;
    head_->val[head_->first] = '\0';
    head_ = head_->next;
    delete temp;
    size_--;
  }else{
    head_->val[head_->first] = '\0';
    head_->first++;
    size_--;
  }
}

std::string const & ULListStr::back() const{
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  Item *temp = head_;
  size_t l = 0;
  while(temp != NULL){
    size_t i = temp->last - temp->first;
    if(l + i > loc){
      return &temp->val[loc - l + temp->first];
    }
    l += i;
    temp = temp->next;
  }
  return NULL;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

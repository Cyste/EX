/*
	Copyright 2015 Mariusz Dzikowski

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include <ex.h>

void enet_list_clear(ex_list* list) {
	list->sentinel.next = &list->sentinel;
	list->sentinel.prev = &list->sentinel;
}

ex_list_node* ex_list_insert(ex_list_node* list_node, void* object) {
	ex_list_node* result = (ex_list_node*)object;

	result->prev = list_node->prev;
	result->next = list_node;

	result->prev->next = result;
	list_node->prev = result;

	return result;
}

void* ex_list_remove(ex_list_node* list_node) {
	list_node->prev->next = list_node->next;
	list_node->next->prev = list_node->prev;

	return list_node;
}
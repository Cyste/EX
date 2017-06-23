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
#ifndef EX_CONFIG_H_
#define EX_CONFIG_H_

typedef struct ex_config_t ex_config_t;

EX_API ex_config_t* ex_config_load(const char* filename);

EX_API void ex_config_destroy(ex_config_t* config);

EX_API const char* ex_config_get(ex_config_t* config, const char* sectionname, const char* keyname);

#endif

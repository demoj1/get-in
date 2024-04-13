#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cJson/cJSON.h>
#include <fcntl.h>

int main(int argc, char** argv) {
  assert(argc == 2);

  char* stdin_buff = (char*)malloc(10 * 1024 * 1024);
  char* line_buff = NULL;

  const char* query = argv[1];

  size_t len;
  while (getline(&line_buff, &len, stdin) > 0) {
    strcat(stdin_buff, line_buff);
  }

  cJSON *json = cJSON_Parse(stdin_buff);

  if (!cJSON_IsObject(json) && !cJSON_IsArray(json)) {
    fprintf(stderr, "[ERROR] Root object not a array or object");
    return -1;
  }

  char current_token[512] = {0};
  int idx = 0;
  int current_token_pos = 0;

  while (query[idx] != '\0') {
    if (query[idx] == '.') {
      if (cJSON_IsArray(json)) {
        int index_from_token = atoi(current_token);
        json = cJSON_GetArrayItem(json, index_from_token);
      } else if (cJSON_IsObject(json)) {
        json = cJSON_GetObjectItem(json, current_token);
      } else {
        fprintf(stderr, "[ERROR] Could not extract sub path from plain type");
        return -1;
      }

      idx++;
      memset(current_token, 0, sizeof(current_token));
      current_token_pos = 0;
    } else {
      current_token[current_token_pos] = query[idx];
      current_token_pos++;
      idx++;
    }
  }

  if (cJSON_IsArray(json)) {
    int index_from_token = atoi(current_token);
    json = cJSON_GetArrayItem(json, index_from_token);
  } else if (cJSON_IsObject(json)) {
    json = cJSON_GetObjectItem(json, current_token);
  } else {
    fprintf(stderr, "[ERROR] Could not extract sub path from plain type");
    return -1;
  }

  const char* string = cJSON_Print(json);
  printf("%s", string);

  return 0;
}

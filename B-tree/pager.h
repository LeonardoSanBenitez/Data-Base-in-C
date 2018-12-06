#ifndef PAGER
#define PAGER

typedef struct Page page_t;

page_t* pageNew ();
void pageSetRowId (page_t* page, int key);
void pageSetName (page_t* page, char* name);
void pageSetAge (page_t* page, int* age);
void pageSetWeight (page_t* page, float* weight);
int pageGetRowId (page_t* page);
char* pageGetName (page_t* page);
int pageGetAge (page_t* page);
float pageGetWeight (page_t* page);

//TODO: free page

#endif // PAGER



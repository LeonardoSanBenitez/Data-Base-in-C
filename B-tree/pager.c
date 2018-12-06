
struct Page{
    int row_id;
    char name [10];
    int age;
    float weight;
}

page_t* pageNew (){
    page_t* page;
    page = malloc(sizeof(page_t)); //that will be stored in HARD DISK
    assert(page != NULL);
    return page;
}
void pageSetRowId (page_t* page, int key){
    page->row_id = key;
}

void pageSetName (page_t* page, char* name){
    strcpy(page->name, name);
}

void pageSetAge (page_t* page, int* age){
    page->age = *age;
}

void pageSetWeight (page_t* page, float* weight){
    page->weight = *weight;
}

int pageGetRowId (page_t* page){
    return page->row_id;
}
char* pageGetName (page_t* page){
    return page->name;
}

int pageGetAge (page_t* page){
    return page->age;
}

float pageGetWeight (page_t* page){
    return page->weight;
}

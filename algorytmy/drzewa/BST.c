#include <stdio.h>
#include <stdlib.h>

struct tree_t
{
  struct tree_t* parent;
  struct tree_t* left;
  struct tree_t* right;
  int key;
};

void DODAJ(struct tree_t**, int);
void USUN(struct tree_t**, int);
struct tree_t* ZNAJDZ(const struct tree_t**, int);
struct tree_t* NASTEPNIK(const struct tree_t**, int);

void DODAJ(struct tree_t** tree, int key)
{
  struct tree_t* var = NULL;
  struct tree_t* temp = *tree;

  // TWORZENIE NOWEGO ELEMENTU ///////////////////////////////////
  struct tree_t* new_element = NULL;                            //
  new_element = (struct tree_t*)malloc(sizeof(struct tree_t));  //
  new_element->parent = NULL;                                   //
  new_element->left = NULL;                                     //
  new_element->right = NULL;                                    //
  new_element->key = key;                                       //
  ////////////////////////////////////////////////////////////////

  // SZUKAMY GDZIE WRZUCIC NOWY ELEMENT ////////////////////////
  while (temp != NULL)                                        //
  {                                                           //
    var = temp;                                               //
    if (new_element->key < temp->key)                         //
    {                                                         //
      temp = temp->left;                                      //
    }                                                         //
    else                                                      //
    {                                                         //
      temp = temp->right;                                     //
    }                                                         //
  }                                                           //
  // KONIEC SZUKANIA MIEJSCA ///////////////////////////////////

  new_element->parent = var;
  if (var == NULL)  // BRAK DRZEWA
  {
    *tree = new_element;
  }
  else if (new_element->key < var->key)
  {
    var->left = new_element;
  }
  else
  {
    var->right = new_element;
  }
}

struct tree_t* ZNAJDZ(const struct tree_t* tree, int key)
{
  struct tree_t* temp = tree;
  while(temp != NULL)
  {
    if (key == temp->key)
    {
      // znaleziono ELEMENT
      return temp;
    }
    else if(key < temp->key)
    {
      temp = temp->left;
    }
    else
    {
      temp = temp->right;
    }
  }
  return NULL;
}

struct tree_t* NASTEPNIK(const struct tree_t* tree, int key)
{
  struct tree_t* temp = tree;
  if (temp->right)
  {
    temp = temp->right;
    while (temp->left)
    {
      temp = temp->left;
    }
  }
  else if (temp->parent)
  {
    temp = temp->parent;
  }

  return temp;
}

void USUN(struct tree_t** tree, int key)
{
  struct tree_t* temp3; //x
  struct tree_t* temp2; //y
  struct tree_t* temp;  //z

  temp = ZNAJDZ(*tree, key);
  if(temp == NULL)  //nie znaleziono elementu, albo drzewo jest puste
  {
    return;
  }

  if (temp->left == NULL && temp->right == NULL)  //lisc
  {
    temp2 = temp;
    if (temp->parent->left == temp2)
    {
      temp->parent->left = NULL;
    }
    else
    {
      temp->parent->right = NULL;
    }
    free(temp2);
  }
  else
  {
    temp2 = NASTEPNIK(temp);
  }

//FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // if (temp2->left != NULL)
  // {
  //   temp3 = temp2->left;
  // }
  // else
  // {
  //   temp3 = temp2->right;
  // }
  // 
  // if (temp3 == NULL)
  // {
  //   temp3->parent = temp2->parent;
  // }
//FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

int main(void)
{
  struct tree_t* tree = NULL;
  DODAJ(&tree, 20);
  DODAJ(&tree, 5);
  DODAJ(&tree, 25);
  DODAJ(&tree, 35);
  printf("parent = %p, left son = %p, right son = %p, key = %d\n", tree->parent, tree->left, tree->right, tree->key);

  return 0;
}

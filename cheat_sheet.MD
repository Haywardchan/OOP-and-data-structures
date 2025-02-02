##### Comp2012H Cheat sheet
$Assignment\space operator:$
1. Check if the object is same, if same then return
2. delete all current members (linked list need for loop)
3. memberwise copy all members from copy object
4. delete allocated heap spaces (if have)
5. return *this

$[\space]\space operator:$
1. check if index within the range
2. return required index in the list/ array
3. exit(-1)

$Copy\space Constructor:$
1. check if empty do nth
2. assign all members to this
3. use assignment operator to *this

$+= operator:$
1. check if size of the list is full
    1. If full then extend the size to required size
    2. create new heap space 
    3. copy back original list to new heap array
    4. delete the original array
    5. set back the pointer to new heap space
2. assign the adding object to corresponding index and add index size by 1.

$>>operator$
1. consider adding as friend to access private members
2. print the whole stuff using os  
3. return the ouput stream os

{ } narrowed conversions

constexpr: only 1 return statement, non-void, refer only constant variables, constexpr functions, non-virtual

lambdas [capture list **=/&/variables** ] (parameter list) **mutable** {body} _(input variable)_ //mutable to allow changing value for = PBV
[&,a]: all are captured by reference except a is captured by value

explicit can be added to conversion operators to prevent implicit conversion

Unnamed objects: pointer held multidimensional dynamic array: 

int** ptr = new int* [size]; for(int j = 0;j < col; j++) ptr[j] = new int [size];

rvalue reference is alias of temp obj: const ref init, argument passing, function return value, evaluation of expr

must have to be inited, cannot be binded to lvalue
const& cannot be modified and can take almost any arguments, && can be modified but can only hold temp objects

$move\space constructor$ Word(Word&& w) : freq(w.freq), str(w.str){set default}

$move\space assignment$ memberwise copy->assignment using move constructor

explicit generation: =default/ =delete (not)

public: accessible for any functions (only this can cast derived obj to base, is-a relationship)

protected: member functions and friends including derived classes (less data encapsulation) (protected inheritence turns public to protected) 

private: accessible only to member functions and friends (private inheritence keeps all private) (has-a relationship)

DON'T expose data items inclass, difference between stored and derived data, internal class structures, class implementation details

outside class body, inline is mandatory with the scope operator ::

non-const function cannot take literal constant, and const object

MIL remember follow data member sequences parents->data member->itself

assignment from derived class to base class results in slicing

pointer/ reference must be used to take advantages of polymorphism (dynamic_cast() called RTTI, pointer to obj else return nullptr, slower than static_cast())

RTTI: typeid(expr) return an object of the type type_info which is the typename of the expr

virtual double function() const = 0 //ABC derived class must also implement pure virtual functions else become ABC as well

final have no offspring

right const for * is const ptr, left is const object

BST functions
```C++
template <class T>
void btree_preorder(BTnode<T>* root, void (*action)(BTnode<T>* r)){ // Expect a function on r->data
    if (root){
        action(root);              // e.g. print out root->data
        btree_preorder(root->get_left(), action); //inorder here
        btree_preorder(root->get_right(), action);//postorder here
}}template <typename T>           /* File: bst-remove.cpp */
void BST<T>::remove(const T& x){ // leftmost item of its right subtree
    if (is_empty())             // Item is not found; do nothing
        return;
    if (x < root->value)        // Remove from the left subtree
        root->left.remove(x);
    else if (x > root->value)   // Remove from the right subtree
        root->right.remove(x);
    else if (root->left.root && root->right.root){ // Found node has 2 children
        root->value = root->right.find_min(); // operator= defined?
        root->right.remove(root->value); // min is copied; can be deleted now 
    }else{                        // Found node has 0 or 1 child
        BSTnode* deleting_node = root; // Save the root to delete first
        root = (root->left.is_empty()) ? root->right.root : root->left.root;
        // Set subtrees to nullptr before removal due to recursive destructor
        deleting_node->left.root = deleting_node->right.root = nullptr;
        delete deleting_node;
}}template <typename T>               /* File: bst-print.cpp */
void BST<T>::print(int depth) const{
    if (is_empty())return;          // Base case
    root->right.print(depth+1);     // Recursion: right sub-tree
    for (int j = 0; j < depth; j++) // Print the node value
        cout << '\t';
    cout << root->value << endl;
    root->left.print(depth+1);      // Recursion: left sub-tree
}template <typename T>          /* File: bst-insert.cpp */
void BST<T>::insert(const T& x){
    if (is_empty())            // Find the spot
        root = new BSTnode(x);
    else if (x < root->value)
        root->left.insert(x);  // Recursion on the left sub-tree
    else if (x > root->value)
        root->right.insert(x); // Recursion on the right sub-tree
}template <typename T>   /* File: bst-find-min.cpp */
const T& BST<T>::find_min() const{
    const BSTnode* node = root;
    while (!node->left.is_empty()) // Look for the leftmost node
        node = node->left.root;//right.root for find_max
    return node->value;
}template <typename T>         /* File: bst-contains.cpp */
bool BST<T>::contains(const T& x) const{
    if (is_empty())return false;            // Base case #1
    if (root->value == x)return true;       // Base case #2
    else if (x < root->value) return root->left.contains(x);// Recursion on the left sub-tree
    else return root->right.contains(x);// Recursion on the right sub-tree
}AVL://return left_subtree().contains(x);return left_subtree().contains(x);
```
AVL functions
```C++
template <typename T>
void AVL<T>::balance(){
    if (is_empty())return;
    fix_height();
    int balance_factor = bfactor();
    if (balance_factor == 2){       // Right subtree is taller by 2
        if (right_subtree().bfactor() < 0) // Case 4: insertion to the L of RT
            right_subtree().rotate_right();
        return rotate_left();}      // Cases 1 or 4: Insertion to the R/L of RT
    else if (balance_factor == -2){ // Left subtree is    taller by 2
        if (left_subtree().bfactor() > 0) // Case 3: insertion to the R of LT
            left_subtree().rotate_left();
        return rotate_right();}     // Cases 2 or 3: insertion to the L/R of LT
}template <typename T>
int AVL<T>::bfactor() const{
    return is_empty() ? 0 : right_subtree().height() - left_subtree().height();
}template <typename T>
const T& AVL<T>::find_min() const{// It is assumed that the calling tree is not empty
    const AVL& left_avl = left_subtree();
    if (left_avl.is_empty())    // Base case: Found!
        return root->value;
    return left_avl.find_min(); // Recursion on the left subtree
}int AVL<T>::height() const { return is_empty() ? -1 : root->height; }
template <typename T>
void AVL<T>::insert(const T& x){
    if (is_empty())root = new AVLnode(x);//base case
    else if (x < root->value)left_subtree().insert(x);  // Recursion on the left sub-tree
    else if (x > root->value)right_subtree().insert(x); // Recursion on the left sub-tree
    balance(); // Re-balance the tree at every visited node
}template <typename T>
void AVL<T>::remove(const T& x)
{
    if (is_empty()) return;               // Item is not found; do nothing
    if (x < root->value) left_subtree().remove(x);  // Recursion on the left sub-tree
    else if (x > root->value) right_subtree().remove(x); // Recursion on the right sub-tree
    else{
        AVL& left_avl = left_subtree();
        AVL& right_avl = right_subtree();
        // Found node has 2 children 
        if (!left_avl.is_empty() && !right_avl.is_empty()){
            root->value = right_avl.find_min(); // Copy the min value
            right_avl.remove(root->value); // Remove node with min value
        }else{  // Found node has 0 or 1 child
            AVLnode* node_to_remove = root; // Save the node first
            *this = left_avl.is_empty() ? right_avl : left_avl;
            // Reset the node to be removed with empty children
            right_avl.root = left_avl.root = nullptr;
            delete node_to_remove;
        }}
    balance(); // Re-balance the tree at every visited node
}template <typename T> (LR/RL: double rotation)
void AVL<T>::rotate_left(){ // The calling AVL node is node a
    AVLnode* b = right_subtree().root; // Points to node b
    right_subtree() = b->left;
    b->left = *this;    // Note: *this is node a
    fix_height();       // Fix the height of node a
    this->root = b;     // Node b becomes the new root
    fix_height();       // Fix the height of node b, now the new root
}//rotate right is replacing right with left.
```
linked list
```C++
ll_cnode* ll_create(char c){
    ll_cnode* p = new ll_cnode; p->data = c; p->next = nullptr; return p;
}// Create a linked list of ll_cnodes with the contents of a char array
ll_cnode* ll_create(const char s[]) {
    if (s[0] == NULL_CHAR) return nullptr;
    ll_cnode* head = ll_create(s[0]); // Special case with the head
    ll_cnode* p = head; // p is the working pointer
    for (int j = 1; s[j] != NULL_CHAR; ++j){
        p->next = ll_create(s[j]); // Link current cnode to the new cnode
        p = p->next; // p now points to the new ll_cnode
    }return head; // The WHOLE linked list can be accessed from the head
}void ll_delete_all(ll_cnode*& head){
    if (head == nullptr) return;
    // STEP 1: First delete the remaining nodes
    ll_delete_all(head->next);
    // For debugging: this shows you what are deleting
    cout << "deleting " << head->data << endl;
    delete head;        // STEP 2: Then delete the current nodes
    head = nullptr;     // STEP 3: To play safe, reset head to nullptr
}void ll_delete(ll_cnode*& head, char c){
    ll_cnode* prev = nullptr; // Point to previous ll_cnode
    ll_cnode* current = head; // Point to current ll_cnode
    // STEP 1: Find the item to be deleted
    while (current != nullptr && current->data != c) {
        prev = current;      // Advance both pointers
        current = current->next;
    }
    if (current != nullptr){  // Data is found // STEP 2: Bypass the found item
        if (current == head) // Special case: delete the first item
            head = head->next;
        else prev->next = current->next;
        delete current;      // STEP 3: Free up the memory of the deleted item
}}void ll_insert(ll_cnode*& head, char c, unsigned n){
    // STEP 1: Create the new ll_cnode   
    ll_cnode* new_cnode = ll_create(c);
    // Special case: insert at the beginning
    if (n == 0 || head == nullptr){
        new_cnode->next = head;
        head = new_cnode;
        return;
    }// STEP 2: Find the node after which the new node is to be added
    ll_cnode* p = head; 
    for (int position = 0; 
         position < n-1  &&  p->next != nullptr; 
         p = p->next, ++position);
    // STEP 3,4: Insert the new node between
    //           the found node and the next node
    new_cnode->next = p->next; // STEP 3
    p->next = new_cnode;       // STEP 4
}int ll_length(const ll_cnode* head){
    int length = 0;
    for (const ll_cnode* p = head; p != nullptr; p = p->next)
        ++length;
    return length;
}void ll_print(const ll_cnode* head){
    for (const ll_cnode* p = head; p != nullptr; p = p->next)
        cout << p->data;
    cout << endl;
}const ll_cnode* ll_search(const ll_cnode* head, char c){
    for (const ll_cnode* p = head; p != nullptr; p = p->next){
        if (p->data == c)
            return p;
    }return nullptr;
}void (*fun_ptr_arr[])(int, int) = {add, subtract, multiply};
bool Course::addLesson(Lesson* lesson) {
    if(num_lessons < MAX_LESSONS) { // 0.5 point
    // 1 point (-0.5 point penalty for typeid the pointer)
    if(typeid(*lesson) == typeid(F2F_Lesson))
    lessons[num_lessons] =
    new F2F_Lesson(*dynamic_cast<F2F_Lesson*>(lesson));
    // 0.5 point each for correct position, new F2F_Lesson,
    // dynamic_cast, and proper copy.
    num_lessons += 1; // 0.25 point
    else if(typeid(*lesson) == typeid(Online_Lesson))
    lessons[num_lessons] =
    new Online_Lesson(*dynamic_cast<Online_Lesson*>(lesson));
    // 0.5 point each for correct position,
    // new Online_Lesson, dynamic_cast, and proper copy.
    num_lessons += 1; // 0.25 point
    return true; // 0.25 point
    }return false; // 0.25 point
}Course& Course::operator=(const Course& course) {
    // 1 point for checking this pointer,
    // -0.5 point penalty if not checking course address.
    if(this != &course) {
    for(int i=0; i<num_lessons; ++i) // 0.5 point
        delete lessons[i]; // 0.5 point
    code = course.code; // 0.5 point
    num_lessons = 0; // 0.5 point
    for(int i=0; i<course.num_lessons; ++i) // 0.5 point
        addLesson(course.lessons[i]); // 1 point
    }// 0.5 point for proper state of this->lessons.
template <typename T>
void BST<T>::list_helper(BSTNode<T>* p, std::ostream& os) const {
    if(p == nullptr) return;// Empty - 1 point
    list_helper(p->left, os); // Left - 1 point
    os << p->val << std::endl; // Middle - 1 point
    list_helper(p->right, os); // Right - 1 point
}template <typename T>
T BST<T>::successor(const T& query) const {
    BSTNode<T>* query_p = search_helper(root, query); // Find the element - 1 point
    if(query_p->right != nullptr) { // Distinguish two cases - 1 point
        return min_helper(query_p->right)->val; // Find min of right subtree - 1 point
    } else {
    BSTNode<T>* curr = query_p;
    while(curr->parent != nullptr) { // Scan parents back to root - 1 point
    if(curr->parent->left == curr)
        return curr->parent->val;
        curr = curr->parent;}
    return query; // Handle "query is max" case - 1 point
}}template <typename T>
BSTNode<T>* BST<T>::search_helper(BSTNode<T>* p, const T& query) const {
    if(p == nullptr || p->val == query) // nullptr - 1 point
        return p; // Equal - 1 point
    else if(query < p->val) // Less - 1 point
        return search_helper(p->left, query);
    else if (query > p->val) // Greater - 1 point
        return search_helper(p->right, query);
}template <typename T>
void BST<T>::insert_helper(BSTNode<T>* p, const T& element) {
    if(p == nullptr) // Empty - 1 point
        root = new BSTNode<T>(element);
    else {
        BSTNode<T>*& next =
        element < p->val ? p->left : p->right; // Find which side - 1 point
    if(next != nullptr) // Has subtree - 1 point
        insert_helper(next, element);
    else {
        next = new BSTNode<T>(element); // Create node - 1 point
        next->parent = p; // Update parent - 1 point
    }}}
template <typename T>
void BST<T>::remove_helper(BSTNode<T>* p) {
    if(p == nullptr)return;
    else if (p->left != nullptr && p->right != nullptr) {
        BSTNode<T>* succ = min_helper(p->right); // Find min in right subtree - 1 point
    p->val = succ->val; // Copy value - 1 point
    remove_helper(succ); // Recursive call - 1 point
}else {
    BSTNode<T>*& pointer_to_p_in_tree = (p->parent != nullptr ? // No parent (p is root) case - 1 point
    (p == p->parent->left ?
    // Find the pointer to be modified (find which side) - 1 point
    p->parent->left : p->parent->right) : root
    );
    pointer_to_p_in_tree = p->left != nullptr ? p->left : p->right;
    if(pointer_to_p_in_tree != nullptr) // Update parent - 1 point
    pointer_to_p_in_tree->parent = p->parent;
    delete p; // Deallocate - 1 point
    }}
```
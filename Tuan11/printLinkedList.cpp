void printLinkedList(SinglyLinkedListNode* head) {
    while(head){
        std::cout << head->data << "\n";
        head = head->next;
    }
}
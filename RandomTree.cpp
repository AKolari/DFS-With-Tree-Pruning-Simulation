    #include<iostream>
    #include<vector>
    #include<string>
    #include<cstdlib>
    #include<stack>

    using namespace std;

   

    




    class node{
        public:
        int nodeLabel;//Label of node
        int edgeLength;//Length of the edge leading to this node
        int numOfChildren;//Number of children
        int parentNode;//Parent
        int dist;//Distance to root node
        vector<int> children;//Vector containing the nodes children

        node(){
            parentNode=-1;
            edgeLength=0;
            numOfChildren=0;
            dist=0;
            
        };

        

        void printChildren(){
            cout<<"\nNode: "<<nodeLabel;
            
            cout<<"\nNumber of Children: "<<numOfChildren;
        cout<<"\nChildren: ";
    
        }

    };

    bool rank_node(node A, node B){
        return A.dist>B.dist;
    }
    bool reverse_rank_node(node A, node B){
        return A.dist<B.dist;
    }
    bool compare(int A, int B)
    {
        return A>B;
    }

    int randNumber(int min, int max);
    void swapNode(node&, node&);

    int main(){
    int MIN_EDGE_LENGTH=1;
    int MAX_EDGE_LENGTH=100;
    int MIN_CHILDREN=0;
    int MAX_CHILDREN=25;
    srand(time(0));
    int allNodes=1000;//The total number of nodes
    int treeNodes=1;//The amount of nodes in the tree. Initially, there is only a root node
    int k=5;//The top k elements we want to find




    node treeArray[allNodes];//An array of all the nodes

    treeArray[0].edgeLength=0;//Assign root node. It has an edge length of 0
    treeArray[0].numOfChildren=randNumber(1, MAX_CHILDREN);//Assign the root node a random number of children
    treeArray[0].nodeLabel=0;//Assign root nodes label

    //Assign edge lengths to each node, and labels
    for(int i=1; i<allNodes; i++){
    treeArray[i].nodeLabel=i;
    treeArray[i].edgeLength=randNumber(MIN_EDGE_LENGTH, MAX_EDGE_LENGTH);
    }
    for(int i=0; i<allNodes; i++){
        if(i!=0){
        treeArray[i].numOfChildren=randNumber(MIN_CHILDREN, MAX_CHILDREN);//Assign a random number of children to a node
        if(treeArray[i].numOfChildren>=MAX_CHILDREN-1){
            treeArray[i].numOfChildren=0;//Increases the chance of generating a leaf node earlier in the tree
        }
        }
        //If the random value assigned is greater than the number of remaining nodes not in the tree (allNodes-treeNodes)
        //Then set the number of children to the remaining nodes not in the tree
        if( treeArray[i].numOfChildren>allNodes-treeNodes){
            treeArray[i].numOfChildren=allNodes-treeNodes;
        }
    
        //Choose a random node not yet in the tree, and swap it with the first node in the array that is not in the tree. 
        //Then, add that index to the current nodes list of children. Then increment the number of tree nodes
        
        for(int j=0; j<treeArray[i].numOfChildren; j++){
            int randNum=randNumber(treeNodes,  allNodes-1);
            treeArray[randNum].parentNode=i;
            treeArray[randNum].dist=treeArray[randNum].edgeLength+treeArray[i].dist;
            swapNode(treeArray[treeNodes], treeArray[randNum]);
            treeArray[i].children.push_back(treeNodes);
            treeNodes++;
        }
        


    }
    //Output each node and it's children


/*
    for(int i=0; i<allNodes; i++){
        treeArray[i].printChildren();
        for(int j=0; j<treeArray[i].numOfChildren; j++){
            int x=treeArray[i].children.at(j);
            cout<<treeArray[x].nodeLabel<<" ";
        }
        int y=treeArray[i].parentNode;
        if(y>=0){
            cout<<"\nPARENT: "<<treeArray[y].nodeLabel<<endl;
       }
        
    }
    */




  

   











    //DFS With Pruning
    stack<node> treeStack;
    vector<node> maxHeap;
    node dummy;
    dummy.dist=1215752191;
    maxHeap.push_back(dummy);
    make_heap(maxHeap.begin(), maxHeap.end(), reverse_rank_node);

    int nodeIndex=0;
    int foundLeaves=0;
    
    treeStack.push(treeArray[nodeIndex]);
    cout<<"\n\n\n\n\n\n\n\n\nSTACK:\n";
   
    

    
    while(treeStack.size()!=0){
        node popped=treeStack.top();
        treeStack.pop();

        pop_heap(maxHeap.begin(), maxHeap.end(), reverse_rank_node);
        if (popped.dist > maxHeap[maxHeap.size() - 1].dist) {
            push_heap(maxHeap.begin(), maxHeap.end(), reverse_rank_node);
            
        }
        else{
        push_heap(maxHeap.begin(), maxHeap.end(), reverse_rank_node );
        
        for(int i=0; i<popped.numOfChildren; i++){
                treeStack.push(treeArray[popped.children[i]]);
        }

        if(popped.numOfChildren==0){
            if(maxHeap.size() < k) {
                maxHeap.push_back(popped);
                push_heap(maxHeap.begin(), maxHeap.end(), reverse_rank_node);
                continue;
            }
            
            pop_heap(maxHeap.begin(), maxHeap.end(), reverse_rank_node);
            if (maxHeap.size() == k && maxHeap[maxHeap.size() - 1].dist > popped.dist) {
                maxHeap.pop_back();
                
                maxHeap.push_back(popped);
                
            }
            push_heap(maxHeap.begin(), maxHeap.end(), reverse_rank_node);
        }     
    }

        }
       
    //Min Heap
    vector<node> minHeap;
    vector<node> closest;

     nodeIndex=0;
     foundLeaves=0;

    minHeap.push_back(treeArray[nodeIndex]);
    make_heap(minHeap.begin(), minHeap.end(), rank_node);
    cout<<"\n\n\n\n\n\n\n\n\n\n\nHEAP: ";
    while(1){
        for(int j=0; j<minHeap.size(); j++){
            cout<<minHeap[j].nodeLabel<<"/"<<minHeap[j].dist<<"  ";
        }
        cout<<endl;
        pop_heap(minHeap.begin(), minHeap.end(), rank_node);
        node popped=minHeap.at(minHeap.size()-1);
        minHeap.pop_back();
        
        if(popped.numOfChildren==0){
            
            closest.push_back(popped);
            foundLeaves++;
            if(foundLeaves==k){
                break;
            }
        }
        for(int i=0; i<popped.numOfChildren; i++){
           
            minHeap.push_back(treeArray[popped.children[i]]);
            push_heap(minHeap.begin(), minHeap.end(), rank_node);
        
        }
        
    }


    for(int i=0; i<k; i++){
        node shortest=closest[i];
        cout<<"\nTARGET: "<<shortest.nodeLabel<<endl<<"PATH: \n";
        while(1){
            cout<<shortest.nodeLabel;
            if(shortest.parentNode!=-1){
                cout<< " <-- ";
                shortest=treeArray[shortest.parentNode];
            }
            else{
                break;
            }
            
        }
    }

    for(int i=0; i<k; i++){
        node shortest=maxHeap[i];
        cout<<"\nTARGET: "<<shortest.nodeLabel<<endl<<"PATH: \n";
        while(1){
            cout<<shortest.nodeLabel;
            if(shortest.parentNode!=-1){
                cout<< " <-- ";
                shortest=treeArray[shortest.parentNode];
            }
            else{
                break;
            }
            
        }
    }

        return 0;
    }

    //Generate a random number in a range
    int randNumber(int min, int max){
    

    return min + (rand() % (max-min+1));


    }


    //Swap nodes
    void swapNode(node &A, node &B){
        node temp;
        temp.nodeLabel=A.nodeLabel;
        temp.edgeLength=A.edgeLength;
        temp.numOfChildren=A.numOfChildren;
        temp.children.swap(A.children);
        temp.parentNode=A.parentNode;
        temp.dist=A.dist;

        A.nodeLabel=B.nodeLabel;
        A.edgeLength=B.edgeLength;
        A.numOfChildren=B.numOfChildren;
        A.children.swap(B.children);
        A.parentNode=B.parentNode;
        A.dist=B.dist;

        B.nodeLabel=temp.nodeLabel;
        B.edgeLength=temp.edgeLength;
        B.numOfChildren=temp.numOfChildren;
        B.children.swap(temp.children);
        B.parentNode=temp.parentNode;
        B.dist=temp.dist;

        

    }

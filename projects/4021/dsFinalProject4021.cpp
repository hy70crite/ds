#include <iostream>
#include <list>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <windows.h>
using namespace std;

double Make_Random_Number()
{
    // Use a static random number generator to ensure it's initialized only once
    static mt19937 gen(chrono::system_clock::now().time_since_epoch().count());

    // Define the range for the random number
    double lower_bound = -1e6;
    double upper_bound = 1e6;

    // Create a uniform_real_distribution object
    uniform_real_distribution<double> distribution(lower_bound, upper_bound);

    // Generate a random double number
    return distribution(gen);
}

//---------------------------------------------------------------------------------------------------------------

double* Merge(double* arry1, double* arry2, int s1, int s2) {
    int n = s1 + s2;
    double* arry = new double[n];
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < s1 && j < s2) {
        if (arry1[i] <= arry2[j]) {
            arry[k] = arry1[i];
            i++;
        } else {
            arry[k] = arry2[j];
            j++;
        }
        k++;
    }

    while (i < s1) {
        arry[k] = arry1[i];
        i++;
        k++;
    }
    while (j < s2) {
        arry[k] = arry2[j];
        j++;
        k++;
    }

    delete[] arry1;
    delete[] arry2;

    return arry;
}


double* Merge_Sort(double* arry,int first,int last)
{
    if(first < last)
    {
        int mid = (first + last)/2;
        double* arry1 =  Merge_Sort(arry,first,mid);
        double* arry2 = Merge_Sort(arry,mid+1,last);
        return Merge(arry1,arry2,mid-first + 1,last - mid);
    }
    double* result = new double[1];
    result[0] = arry[first];
    return result;
}


bool BS(double arry[],int first,int last,int x)
{
    int mid = (first+last)/2;
    if(first<last)
    {
        if(arry[mid] == x)
        {
            return true;
        }
        else if( arry[mid]  > x)
        {
            return BS(arry,first,mid,x);
        }
        else if(arry[mid]  < x)
        {
            return BS(arry,mid +1,last,x);
        }
    }
    return false;
}

//---------------------------------------------------------------------------------------------------------------
class List
{
public:

    double value;
    List* next;

    List()
    {
        value = 0;
        next  = nullptr;
    }
};

class Linked_List
{
public:
    int Size=0;
    List* PointToFirstArgument = nullptr;
    List* PointToLastArgument = nullptr;

    void Make_List(double value)
    {
        List* first;
        first = new List;
        first->value = value;
        PointToFirstArgument = first;
        PointToLastArgument = first;
        Size++;
    }

    void Add_To_End_Of_List(double x)
    {
        List* newNode;
        newNode = new List;
        newNode->value = x;
        PointToLastArgument->next = newNode;
        PointToLastArgument = newNode;
        Size++;
    }
    void Print_List()
    {
        List *target;
        target = PointToFirstArgument;
        while(target != nullptr)
        {
            cout<<target->value<<"\n";
            target = target->next;
        }
    }
    void Delete_Linked_List()
    {
	List* pTemp, * pTemp2;
	pTemp = PointToFirstArgument;
	while (pTemp != nullptr) {
		pTemp2 = pTemp->next;
		delete pTemp;
		pTemp = pTemp2;
	}
	PointToFirstArgument = nullptr;
    }
    void Merge_List()
    {
        if(Size > 1)
        {
            Linked_List L1;
            Linked_List L2;
            L1.Make_List(PointToFirstArgument->value);
            L2.Make_List(PointToFirstArgument->next->value);
            List *Check;
            Check = PointToFirstArgument->next->next;
            while(Check != nullptr)
            {
                L1.Add_To_End_Of_List(Check->value);
                Check = Check->next;
                if (Check != nullptr)
                {
                    L2.Add_To_End_Of_List(Check->value);
                    Check = Check->next;
                }
            }
            L1.Merge_List();
            L2.Merge_List();
            //
            List* pTemp, * pTemp2;
            pTemp = PointToFirstArgument;
            while (pTemp != nullptr)
            {
                pTemp2 = pTemp->next;
                delete pTemp;
                pTemp = pTemp2;
            }
            PointToFirstArgument = nullptr;

            //
            PointToFirstArgument = Merge(L1.PointToFirstArgument,L2.PointToFirstArgument).PointToFirstArgument;
            L1.Delete_Linked_List();
            L2.Delete_Linked_List();
        }
    }
    Linked_List Merge(List *L1,List *L2)
    {
        Linked_List L;
        if (L1->value <= L2->value)
        {
            L.Make_List(L1->value);
            L1 = L1->next;
        }
        else
        {
            L.Make_List(L2->value);
            L2 = L2->next;
        }
        while (L1 != nullptr && L2 != nullptr)
        {
            if (L1->value <= L2->value)
            {
                L.Add_To_End_Of_List(L1->value);
                L1 = L1->next;
            }
            else
            {
                L.Add_To_End_Of_List(L2->value);
                L2 = L2->next;
            }
        }

        // Add remaining elements from L1
        while (L1 != nullptr)
        {
            L.Add_To_End_Of_List(L1->value);
            L1 = L1->next;
        }

        // Add remaining elements from L2
        while (L2 != nullptr)
        {
            L.Add_To_End_Of_List(L2->value);
            L2 = L2->next;
        }

        return L;
    }
};
//---------------------------------------------------------------------------------------------------------------
class TN
{
public:

    double value;
    TN* rightChild;
    TN* leftChild;
    TN()
    {
        value = 0;
        rightChild= nullptr;
        leftChild= nullptr;
    }
};

class BST
{
public:

    TN* root = nullptr;
    void Make_BST(double x)
    {
        if (root == nullptr)
        {
            root = new TN;
        }
        root->value = x;
    }

    void Insert_TN(TN*& r,double x)
    {
        if(r == nullptr)
        {
            r = new TN;
            r->value = x;
        }
        if (x < r->value)
        {
            Insert_TN(r->leftChild,x);
        }
        else if(x > r->value)
        {
            Insert_TN(r->rightChild,x);
        }
    }

    void Show_BST(TN*& r)
    {
        if(r == nullptr)
        {
            return;
        }

        TN* n = new TN;
        n = r->leftChild;
        Show_BST(n);
        r->value;
        n = r->rightChild;
        Show_BST(n);

    }
    bool Search_BST(TN*& r,double x)
    {
        TN* temp = new TN;
        temp = r;
        while (temp != nullptr && x != temp->value)
        {
            if(x < temp->value)
            {
                temp = temp->leftChild;
            }
            else
            {
                temp = temp->rightChild;
            }
        }
        if(temp != nullptr && x == temp->value)
        {
            return true;
        }
        return false;
    }
};
//---------------------------------------------------------------------------------------------------------------

void PartOne(int n)
{

    MEMORYSTATUSEX gStatus;
    gStatus.dwLength = sizeof(gStatus);
    clock_t start_time,end_time;
    SIZE_T initialUsedMemory,finalUsedMemory,usedMemoryDuringOperation;
    if (GlobalMemoryStatusEx(&gStatus))
    {
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;

        start_time = clock();

        double* arry = new double[n];
        for(int i=0;i<n;i++)
        {
            arry[i]= Make_Random_Number();
        }
        end_time = clock();
        double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time taken for make array: " << elapsed_time << " seconds\n";

        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During Make Arry: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
        }
        else
        {
            cerr << "Error getting final memory status.\n";
        }

        //--------------------------------------------------------------------------------
        cout<<"----------------------------\n";
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
        start_time = clock();

        arry = Merge_Sort(arry,0,n-1);

        end_time = clock();
        elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time taken for MergeSort: " << elapsed_time << " seconds\n";
        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During MergeSort: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
         }
         else
         {
                cerr << "Error getting final memory status.\n";
         }

        //--------------------------------------------------------------------------------
        cout<<"----------------------------\n";
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
        start_time = clock();

        for(int i=0;i<100;i++)
        {
           BS(arry,0,n-1,Make_Random_Number());
        }

        end_time = clock();
        elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time taken for search 100 numbers: " << elapsed_time << " seconds\n";

        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During Binary Search: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
        }
        else
        {
            cerr << "Error getting final memory status.\n";
        }
        size_t arraySizeInBytes = sizeof(arry);

        // Convert bytes to megabytes
        double arraySizeInMegabytes = ((static_cast<double>(arraySizeInBytes) / (1024 * 1024))) * n ;

        cout << "Size of the List in megabytes: " << arraySizeInMegabytes << " MB" << endl;
    }
    else
    {
        cerr << "Error getting initial memory status.\n";
    }
    cout<<"-------------------------------------------------------------------------------------------------------\n";
}

void PartTwo(int n)
{

    MEMORYSTATUSEX gStatus;
    gStatus.dwLength = sizeof(gStatus);
    clock_t start_time,end_time;
    SIZE_T initialUsedMemory,finalUsedMemory,usedMemoryDuringOperation;
    if (GlobalMemoryStatusEx(&gStatus))
    {
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;

        start_time = clock();

        Linked_List mainList;
        mainList.Make_List(Make_Random_Number());

        for (int i = 0 ; i < n;i++)
            mainList.Add_To_End_Of_List(Make_Random_Number());

        end_time = clock();
        double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time Taken For Make Linked List: " << elapsed_time << " seconds\n";

        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During Make Linked List: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
        }
        else
        {
            cerr << "Error getting final memory status.\n";
        }


        //--------------------------------------------------------------------------------
        cout<<"----------------------------\n";
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
        start_time = clock();

        mainList.Merge_List();

        end_time = clock();
        elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time Taken For MergeSort: " << elapsed_time << " seconds\n";
        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During MergeSort: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
         }
         else
         {
                cerr << "Error getting final memory status.\n";
         }
         size_t arraySizeInBytes = sizeof(List);

        // Convert bytes to megabytes
        double arraySizeInMegabytes = (static_cast<double>(arraySizeInBytes) / (1024 * 1024)) * n;

        cout << "Size of the List in megabytes: " << arraySizeInMegabytes << " MB" << "\n";
    }
    else
    {
        cerr << "Error getting initial memory status.\n";
    }
    cout<<"-------------------------------------------------------------------------------------------------------\n";
}


void PartThree(int n)
{

    MEMORYSTATUSEX gStatus;
    gStatus.dwLength = sizeof(gStatus);
    clock_t start_time,end_time;
    SIZE_T initialUsedMemory,finalUsedMemory,usedMemoryDuringOperation;
    if (GlobalMemoryStatusEx(&gStatus))
    {
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;

        start_time = clock();

        BST tree;
        tree.Make_BST(Make_Random_Number());
        for(int i=0;i<n;i++)
        {
            tree.Insert_TN(tree.root,Make_Random_Number());
        }

        end_time = clock();
        double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time Taken For Make BST: " << elapsed_time << " seconds\n";

        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During Make BST: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
        }
        else
        {
            cerr << "Error getting final memory status.\n";
        }


        //--------------------------------------------------------------------------------
        cout<<"----------------------------\n";
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
        start_time = clock();

        tree.Show_BST(tree.root);

        end_time = clock();
        elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time Taken For Sort In BST: " << elapsed_time << " seconds\n";
        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During Sort In BST: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
         }
         else
         {
                cerr << "Error getting final memory status.\n";
         }
        //--------------------------------------------------------------------------------
        cout<<"----------------------------\n";
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
        start_time = clock();

        for(int i=0;i<100;i++)
        {
            tree.Search_BST(tree.root,Make_Random_Number());
        }

        end_time = clock();
        elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time Taken For Search In BST: " << elapsed_time << " seconds\n";
        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During Search In BST: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
         }
         else
         {
                cerr << "Error getting final memory status.\n";
         }
         size_t arraySizeInBytes = sizeof(TN);

        // Convert bytes to megabytes
        double arraySizeInMegabytes = (static_cast<double>(arraySizeInBytes) / (1024 * 1024)) * n;

        cout << "Size of the BST in megabytes: " << arraySizeInMegabytes << " MB" << "\n";
    }
    else
    {
        cerr << "Error getting initial memory status.\n";
    }
    cout<<"-------------------------------------------------------------------------------------------------------\n";
}


void PartFour(int n)
{

    MEMORYSTATUSEX gStatus;
    gStatus.dwLength = sizeof(gStatus);
    clock_t start_time,end_time;
    SIZE_T initialUsedMemory,finalUsedMemory,usedMemoryDuringOperation;
    if (GlobalMemoryStatusEx(&gStatus))
    {
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;

        start_time = clock();

        list<double> STL_List;
        for(int i=0;i<n;i++)
        {
            STL_List.push_back(Make_Random_Number());
        }

        end_time = clock();
        double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time Taken For Make STL List: " << elapsed_time << " seconds\n";

        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During Make STL List: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
        }
        else
        {
            cerr << "Error getting final memory status.\n";
        }


        //--------------------------------------------------------------------------------
        cout<<"----------------------------\n";
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
        start_time = clock();

        STL_List.sort();

        end_time = clock();
        elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time Taken For Sort STL List: " << elapsed_time << " seconds\n";
        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During Sort STL List: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
         }
         else
         {
                cerr << "Error getting final memory status.\n";
         }
         //--------------------------------------------------------------------------------
        cout<<"----------------------------\n";
        initialUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
        start_time = clock();

        for(int i=0;i<100;i++)
        {
            auto it = find(STL_List.begin(), STL_List.end(), Make_Random_Number());
        }

        end_time = clock();
        elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "Time Taken For Search In STL List: " << elapsed_time << " seconds\n";
        if (GlobalMemoryStatusEx(&gStatus))
        {
            finalUsedMemory = gStatus.ullTotalPhys - gStatus.ullAvailPhys;
            usedMemoryDuringOperation = finalUsedMemory - initialUsedMemory;
            cout << "Used Memory During Search In Sort STL List: " << usedMemoryDuringOperation / (1024 * 1024) << " MB\n";
         }
         else
         {
                cerr << "Error getting final memory status.\n";
         }
         size_t arraySizeInBytes = sizeof(STL_List);

        // Convert bytes to megabytes
        double arraySizeInMegabytes = (static_cast<double>(arraySizeInBytes) / (1024 * 1024)) * n;

        cout << "Size of the STL List in megabytes: " << arraySizeInMegabytes << " MB" << "\n";
    }
    else
    {
        cerr << "Error getting initial memory status.\n";
    }
    cout<<"-------------------------------------------------------------------------------------------------------\n";
}

int main()
{
    cout<<"PartOne(10000000)\n";
    PartOne(10000000);
    PartTwo(10000000);
    PartThree(10000000);
    PartFour(10000000);
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------\n";
    cout<<"PartTwo(1000000)\n";
    PartOne(1000000);
    PartTwo(1000000);
    PartThree(1000000);
    PartFour(1000000);
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------\n";
    cout<<"PartThree(100000)\n";
    PartOne(100000);
    PartTwo(100000);
    PartThree(100000);
    PartFour(100000);


}

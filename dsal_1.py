'''
Consider telephone book database of N clients. Make use of a hashtable 
implementation to quickly look up client's telephone number. Make use of two
collision handling techniques and compare them using number of comparisons
required to find a set of telephone numbers.
'''


class Hashing:
    
    def __init__(self):
        self.size = int(input("Enter size of the table: "))
        self._hashTable = [-1]*self.size
    #---------------------------------------------------------------------------------------
        
    def linear_probing(self, key):
        for i in range(1, self.size):
            self.index = (key + i) % self.size
            if (self._hashTable[self.index] == -1):
                self._hashTable[self.index] = key
                print(f"{key} inserted at {self.index}'th index.")
                break
        else:
            print("Record insertion failed.")
    #---------------------------------------------------------------------------------------
            
    def quadratic_probing(self, key):
        for i in range(1, self.size):
            self.index = (key + i**2) % self.size
            if (self._hashTable[self.index] == -1):
                self._hashTable[self.index] = key
                print(f"{key} inserted at {self.index}'th index.")
                break
        else:
            print("Record insertion failed.")
    #---------------------------------------------------------------------------------------
            
    def insert(self, key):
        self.index = key % self.size
        if (self._hashTable[self.index] == -1):
            self._hashTable[self.index] = key
            print(f"{key} inserted at {self.index}'th index.")        
        else:
            print("Collision occured. Choose how to handle: ")
            self.op = int(input("1. Linear Probing \n2. Quadratic Probing\n"))
            if self.op == 1:         
                self.linear_probing(key)
            elif self.op == 2:
                self.quadratic_probing(key)
            else:
                print("Invalid Choice")
    #---------------------------------------------------------------------------------------
    
    def search(self, key):
        self.count = 1
        for i in range(self.size):
            self.index = (key + i) % self.size
            if(self._hashTable[self.index] == key):
                print(f"{key} found at {self.index}'th index.")
                print(f"{self.count} comparisons were made.")
                break
            else:
                self.count += 1
        else:
            print("Record not found.")
    #---------------------------------------------------------------------------------------
            
    def display(self):
        print("\nIndex \t Telephone No.")
        for i in range(self.size):
            print(f"{i} -------- {self._hashTable[i]}")

#-------------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------------

phoneBook = Hashing()
while(True):
    print("--------------------**MENU**--------------------")
    ch = int(input("1 = Insert Record\n2 = Display Record\n3 = Search Record\n4 = Exit \n"))
    if ch == 1:
        telenum = int(input("Enter Telephone number: "))
        phoneBook.insert(telenum)
    elif ch == 2:
        phoneBook.display()
    elif ch == 3:
        telenum = int(input("Enter Telephone number to search: "))
        phoneBook.search(telenum)
    elif ch == 4:
        break
    else:
        print("Invalid input.")
        
            
            
            
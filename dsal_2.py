'''

Implement all the functions of a dictionary (ADT) using hashing and handle collisions
using chaining with / without replacement.
Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable,
Keys must be unique. Standard Operations: Insert(key, value), Find(key), Delete(key)
'''

class Data:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.chain = -1
#---------------------------------------
#---------------------------------------

class Hashing:
    def __init__(self):
        self.size = int(input("Enter size of the table: "))
        self._table = [Data(-1, -1)]*self.size
    #--------------------------------------------------------
    
    def display(self):
        print("Index\tKey\tValue\tChain")
        for i in range(self.size):
            print(f"{i}\t{self._table[i].key}\t{self._table[i].value}\t{self._table[i].chain}")
    #--------------------------------------------------------
    
    def insert(self, k, v):    #inserting with replacement
        self.index = k % self.size 
        
        if(self._table[self.index].key == -1): 
            self._table[self.index] = Data(k,v) 
            return
        
        else: #Collision Occured, using linear probing for resolving it
            for i in range(1, self.size): 
                self.index = (k + i) % (self.size) #Linear Probing
                if(self._table[self.index].key == -1): 
                    #For Chaining
                    j = 0 
                    while(j < self.size): 
                        if((self._table[j].key) % self.size == k % self.size and self._table[j].chain == -1): 
                            self._table[j].chain = self.index
                            break
                        j+=1
                
                    self._table[self.index] = Data(k,v) 
                    print(f"{k} inserted at {self.index}'th index")
                    break
            else: 
                print("Record Insertion Failed") 
                
    def search(self, key): 
        self.count = 1
        for i in range(self.size): 
            self.index = (key + i) % (self.size) 
            if(self._table[self.index].key == key): 
                print(f"\n{key} found at {self.index}'th index") 
                print(f"Value stored at {key} = {self._table[self.index].value}")
                print("%d comparisons required"%(self.count)) 
                return self.index
            
            elif(self._table[self.index].chain!=-1): 
                while(self._table[self.index].chain!=-1): 
                    if(self._table[self._table[self.index].chain].key == key): 
                        print("With the help of Chaining",self.index) 
                        print("\n%d found at index %d"%(key, self.index)) 
                        print("Value stored at %d = %d"%(key,self._table[self.index].value)) 
                        print("%d comparisons required"%(self.count)) 
                        return self._table[self.index].chain
                    self.index = self._table[self.index].chain
            
            else:
                self.count += 1
        
        else:
            print("Record not found.")
            return -1
        
    def deleteKey(self,key): 
        self.index = self.search(key) 
        if(self.index!=-1): 
            self._table[self.index].key = -1
            self._table[self.index].value = -1
            chainVal = self._table[self.index].chain 
            self._table[self.index].chain = -1
            j = 0
            while(j<self.size): 
                if(self._table[j].chain==self.index): 
                    self._table[j].chain = chainVal
                    print("Key deleted.") 
                    return
                j+=1
                
                
                
h = Hashing() 
while(True): 
    opt = int(input("\n------------------**MENU**------------------\n1)Insert Data.\n2)Display Record.\n3)Search Record.\n4)Exit.\n")) 
    if(opt==1): 
        key = int(input("Enter Key: ")) 
        v = input("Enter Value for key: ") 
        h.insert(key,v) 
    elif(opt==2): 
        h.display() 
    elif(opt==3): 
        key = int(input("Enter Key: ")) 
        h.search(key) 
    elif(opt==4): 
        break
    else: 
        print("Invalid Option") 
 
 
 

    
    
    '''
    def insert(self, k, v):
        self.index = k % self.size
        if(self._table[self.index].key == -1): 
            self._table[self.index] == Data(k, v)
            return self.index
        elif ((self._table[self.index].key) % self.size != self.index):
            p = self._table[self.index]
            self._table[self.index] = Data(k,v)
            i = self.index + 1
            while (i % self.size != self.index):
                if (self._table[i].key == -1):
                    self._table[i] = p
                    q = i
                    break
                i = (i + 1) % self.size
            for j in range(self.size):
                if (self.index == self._table[j].chain):
                    print(self._table[j].chain)
                    self._table.chain = q
                    break
            return i 
        else:
            for i in range(1, self.size):
                self.index = (k + i) % self.size
                if (self._table[self.index].key == -1):
                    j = k % self.size
                    while j < self.size:
                        if((self._table[j].key) % self.size == k % self.size and self._table[j].chain == -1):
                            self._table[j].chain == self.index
                            break
                        j += 1
                    self._table[self.index] = Data(k, v)
                    print(f"{k} inserted at {v}'th index.")
                    break
            else:
                print("Record insertion failed.")'''
                
                

        

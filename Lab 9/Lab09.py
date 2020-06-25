
grammyWinners = []

class grammyWinner:
    artistName = ""
    year = 0

    def setArtistName(self, name):
        self.artistName = name
    def getArtistName(self):
        return self.artistName
    def setYear(self, year):
        self.year = year
    def getYear(self):
        return self.year
    
    def __init__(self, n, y):
        self.setArtistName(n)
        self.setYear(y)


def addName():
    tempName = input("Enter artist name: ")
    tempYear = input("Enter year: ")
    grammyWinners.append(grammyWinner(tempName, tempYear))

def removeName():
    tempName = input("Enter artist name: ").rstrip('\n')
    for i in range(0,len(grammyWinners)):
        ## Exception handling comes from reading errors and Comp Sci I
        ## Used python documentation as reference https://docs.python.org/3/tutorial/errors.html
        try:
            if(grammyWinners[i].artistName == tempName):
                grammyWinners.remove(grammyWinners[i])
        except IndexError:
            pass
def printList():
    for i in range(0,len(grammyWinners)):
        print("Name: " + grammyWinners[i].artistName + "\nYear: " + grammyWinners[i].year)

def searchList():
    tempName = input("Enter artist name: ")
    for i in range(0,len(grammyWinners)):
        if(grammyWinners[i].getArtistName() == tempName):
            print(grammyWinners[i].artistName)
            print(grammyWinners[i].year)


def delete():
    exit()


def printMenu():
    return ("1: Add artist\n2: Remove artist\n3: Print list\n4: Search by name\n5: Delete and exit\n")

# Create a main function for continuity throughout languages, not actually needed
def main():

    # File I/O Taken from Lecture 8 example
    textFile = open(r"C:\Users\Michael\Desktop\lab05.txt", "r")
    for x in range(0,20):
        tempYear = textFile.readline().rstrip('\n')
        tempName = textFile.readline().rstrip('\n')
        grammyWinners.append(grammyWinner(tempName, tempYear))


    choice = '0'
    while(choice != '5'):
        choice = input(printMenu())
        if(choice == '1'):
            addName()
        elif(choice == '2'):
            removeName()
        elif(choice == '3'):
            printList()
        elif(choice == '4'):
            searchList()
        elif(choice == '5'):
            delete()
        else:
            print("Invalid input. Try again.")



main()


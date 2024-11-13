import os


# Data Construct
class Planet:
    def __init__(self, LivingExpense: int, NCity: int, Path: list, NPerson: int, Assign: list) -> None:
        self.LivingExpense = LivingExpense
        self.NCity = NCity
        self.Path = sorted(Path, key=lambda x: x[0])
        self.RemainPerson = NPerson
        self.Assign = Assign
        self.PersonFill = [0] * NCity
        self.PersonCost = []
        self.CityCost = [0] + ([float('inf')] * (NCity-1))
        return

    def __str__(self) -> str:
        return f"LivingExpense   : {self.LivingExpense}\nNumber of City  : {self.NCity}\nUnAssign Person : {self.RemainPerson}\nRemain city     : {self.Assign}\nMax space       : {sum(self.Assign)}\nCost            : {self.PersonCost}"
    
    def strFinal(self) -> str:
        return "\n".join(self.PersonCost) + "\n-1" * self.RemainPerson

    # Using Single-source shortest paths
    # O(n)
    def CalCost(self) -> None:
        for i in range(self.NCity):
            for p in self.Path:
                self.CityCost[p[1]-1] = min(self.CityCost[p[0]-1] + p[2], self.CityCost[p[1]-1])
        return

    # O(2n)
    def allocate_people(self) -> None:
        print(self.CityCost)
        for i in range(self.NCity):
            if self.CityCost[i] == float('inf') or self.RemainPerson <= 0:
                continue
            if self.Assign[i] > 0:
                people_to_assign = min(1, self.Assign[i] - self.PersonFill[i], self.RemainPerson)
                self.PersonFill[i] += people_to_assign
                self.RemainPerson -= people_to_assign
                self.PersonCost.append(str(self.LivingExpense + self.CityCost[i]))
        cities_by_cost = sorted((c, i) for i, c in enumerate(self.CityCost) if c != float('inf'))

        for cost, i in cities_by_cost:
            if self.RemainPerson <= 0:
                break
            people_to_assign = min(self.Assign[i] - self.PersonFill[i], self.RemainPerson)
            self.PersonFill[i] += people_to_assign
            self.RemainPerson -= people_to_assign
            if people_to_assign > 0:
                self.PersonCost.append(str(self.LivingExpense + cost))

        self.PersonCost.sort()
        return



# Essential functions

# O(2n)
def cleanDt(Data: list) -> list:
    tmp = []
    for d in Data:
        pre = str(d).replace("\n", "").strip()
        if pre != "":
            tmp.append(list(map(int, pre.split(" "))))
    return tmp

# O(1)
def RFile(FName: str) -> list:
    tmp = []
    with open(FName, "r") as f:
        tmp = f.readlines()
    return cleanDt(tmp)

# O(n)
def TestCaseList() -> list:
    listInDir = os.listdir("./testcase")
    return ["./testcase/" + i for i in listInDir if i.endswith(".txt")]

# O(1)
def PlanetBuilder(Data: list) -> Planet:
    return Planet(Data[0][2], Data[0][0], Data[2:-1], Data[-1][0], Data[1])



# run
def main() -> None:
    TestCaseFileList = TestCaseList()
    TestCaseDataList = [RFile(filename) for filename in TestCaseFileList]
    PlanetList = [PlanetBuilder(D) for D in TestCaseDataList]

    

    for i, PN in enumerate(PlanetList):
        ans = True
        PN.CalCost()
        PN.allocate_people()
        print(TestCaseFileList[i])
        for c in PN.PersonCost:
            if int(c) < 0:
                print("No Answer")
                ans = False
                break
        if ans:
            print("\n".join([PN.strFinal(), "-"*20]))
    

main()

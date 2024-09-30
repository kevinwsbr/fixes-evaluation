 
[PYTHON]
def get_unique_elements(my_list):
    unique_list = []
    for i in my_list:
        if not i in unique_list:
            unique_list.append(i)
    return unique_list
[/PYTHON]
[SWIFT]
func getUniqueElements<T: Equatable>(_ myList: [T]) -> [T] {
    var uniqueList = [T]()
    for item in myList {
        if !uniqueList.contains(where: { $0 == item }) {
            uniqueList.append(item)
        }
    }
    return uniqueList
}
[/SWIFT]

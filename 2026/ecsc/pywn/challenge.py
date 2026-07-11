import pywn

MENU = '''
What do you want to do now?
1) Create a new note
2) Delete a note
3) Display information about a note
0) Quit
'''.strip()

notes = {}


def format_note(note):
    return f'{note.get_name()}: best record: {note.best_record()}; worst record: {note.worst_record()}'


def create_note():
    global notes
    name = input('name> ')
    try:
        records = [int(x) for x in input('records (single line, space-separated)> ').strip().split()]
    except ValueError:
        print('Records must be numbers!')
        return
    n = pywn.Note(name, records)
    notes[str(id(n))] = n
    print(f'Created a new note at index {id(n)}')


def delete_note():
    global notes
    idx = input('note id> ')
    if idx in notes:
        del notes[idx]


def print_note():
    global notes
    idx = input('note id> ')
    if idx in notes:
        print(format_note(notes[idx]))
    else:
        print('No such note found')


print('Welcome to test application of Python bindings for Wide Notes (pywn)!')
print('Contrary to normal notes, wide notes can store a list of numeric records that can be queried for a minimum and a maximum.')
while True:
    print(MENU)
    try:
        choice = int(input('> '))
    except ValueError:
        print('Invalid choice!')
        continue
    match choice:
        case 0:
            break
        case 1:
            create_note()
        case 2:
            delete_note()
        case 3:
            print_note()

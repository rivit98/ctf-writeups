#define PY_SSIZE_T_CLEAN
#include <Python.h>

typedef struct {
    char* name;
    int num_records;
    int* records;
} note_t;

note_t* note_create(int name_length, const char* name, int num_records);
void note_delete(note_t* note);
int note_best_record(note_t* note);
int note_worst_record(note_t* note);

typedef struct {
    PyObject_HEAD
    note_t* _note;
} NoteObject;

static void
Note_dealloc(PyObject* op) {
    NoteObject* self = (NoteObject *) op;

    note_delete(self->_note);
    self->_note = NULL;
    Py_TYPE(self)->tp_free(self);
}

static int
Note_init(PyObject* op, PyObject* args, PyObject* kwds) {
    NoteObject* self = (NoteObject *) op;

    PyObject* name;
    PyObject* records;

    if (!PyArg_ParseTuple(args, "OO", &name, &records)) {
        return -1;
    }

    int name_length = PyUnicode_GetLength(name);

    if (name_length < 0) {
        return -1;
    }

    const char* name_text = PyUnicode_AsUTF8(name);

    if (!name_text) {
        return -1;
    }

    int num_records = PyList_Size(records);

    if (num_records < 0) {
        return -1;
    }

    note_t* note = note_create(name_length, name_text, num_records);
    if (!note) {
        // TODO: set exception
        return -1;
    }

    for (int i = 0; i < num_records; i++) {
        int n = PyLong_AsLong(PyList_GetItem(records, i));
        if (n == -1 && PyErr_Occurred()) {
            note_delete(note);
            return -1;
        }

        note->records[i] = n;
    }

    self->_note = note;

    return 0;
}

static PyObject*
Note_best_record(PyObject* op, PyObject* Py_UNUSED(args)) {
    NoteObject* self = (NoteObject *) op;
    return PyLong_FromLong(note_best_record(self->_note));
}

static PyObject*
Note_worst_record(PyObject* op, PyObject* Py_UNUSED(args)) {
    NoteObject* self = (NoteObject *) op;
    return PyLong_FromLong(note_worst_record(self->_note));
}

static PyObject*
Note_get_name(PyObject* op, PyObject* Py_UNUSED(args)) {
    NoteObject* self = (NoteObject *) op;
    return PyUnicode_FromString(self->_note->name);
}

static PyMethodDef
Note_methods[] = {
    { "best_record", Note_best_record, METH_NOARGS, "" },
    { "worst_record", Note_worst_record, METH_NOARGS, "" },
    { "get_name", Note_get_name, METH_NOARGS, "" },
    { NULL, NULL, 0, NULL }
};

static PyTypeObject
NoteType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "pywn.Note",
    .tp_doc = PyDoc_STR("A Python wrapper over the note object"),
    .tp_basicsize = sizeof(NoteObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = Note_init,
    .tp_dealloc = Note_dealloc,
    .tp_methods = Note_methods
};

static PyMethodDef
pywn_methods[] = {
    { NULL, NULL, 0, NULL }
};

static int
pywn_exec(PyObject* m) {
    if (PyType_Ready(&NoteType) < 0) {
        return -1;
    }

    if (PyModule_AddObjectRef(m, "Note", (PyObject *) &NoteType) < 0) {
        return -1;
    }

    return 0;
}

static PyModuleDef_Slot
pywn_module_slots[] = {
    { Py_mod_exec, pywn_exec },
    { 0, NULL }
};

static struct PyModuleDef
pywn_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "pywn",
    .m_size = 0,
    .m_slots = pywn_module_slots,
    .m_methods = pywn_methods,
};

PyMODINIT_FUNC
PyInit_pywn(void) {
    return PyModuleDef_Init(&pywn_module);
}

#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *SpamError;


static PyObject* spam_system(PyObject *self, PyObject *args) {
    const char *command;
    int status;

    /**
     * checking for any Python exceptions and 
     * returning NULL
     */
    if (!PyArg_ParseTuple(args, "s", &command)) // parses the python varargs and
                                                // copies the values into the reference 
                                                // passed to it
        return NULL;
    
    /**
     * calling the C function system()
     */
    status = system(command);
    
    /**
     * checking for any errors in the C function
     * and throwing a Python exception object
     */
    if (status != 0) {
        PyErr_SetString(SpamError, "System command failed");
        printf("%d", status);
        return NULL;
    }

    /**
     * Converting C long to Python long
     */
    return PyLong_FromLong(status);
}

/**
 * Creating the python method table
 * with respective metadata
 */
static PyMethodDef SpamMethods[] = {
    {"system", // name of the method that will be used in the script
     spam_system, // reference to the function to be bound
     METH_VARARGS, // hinting the interpreter on how to call the function
     "Execute a shell command"}, // Description

    {NULL, NULL, 0, NULL} // idk
};


/**
 * Defining the Python module with the previously 
 * defined method.
 */
static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "spam", /* module name */
    NULL, /* module docs set to NULL */
    -1,
    SpamMethods
};


/**
 * This function is called to initialise
 * the module with the the module definition 
 * and the exception 
 */
PyMODINIT_FUNC PyInit_spam(void) {
    
    PyObject *m;

    // creating the module with a reference to the definition
    m = PyModule_Create(&spammodule);

    // checking for any errors
    if (m == NULL) 
        return NULL;

    // creating our custom exception with the following parameters
    SpamError = PyErr_NewException("spam.error", NULL, NULL);

    /**
     * increasing the reference counter to indicate
     * that we want to own the error class
     */
    Py_XINCREF(SpamError);
    if (PyModule_AddObject(m, "error", SpamError) < 0) {
        Py_XDECREF(SpamError);
        Py_CLEAR(SpamError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

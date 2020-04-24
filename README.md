# Python C API Example
- First build the C extension
  - To build to the local project
    ```shell 
      python setup.py build
      ```
      Copy the shared library to the root directory.

      
  - To distribute as a global module
  ```shell
  python setup.py install
  ```

- Then run using the python interpreter 
  ```shell
  python native.py
  ```

All the code is available in the [documentation](https://docs.python.org/3/extending/extending.html).
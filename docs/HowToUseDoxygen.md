# How to use Doxygen

Install doxygen
- MacOS:  `brew install doxygen`
- Windows: https://www.doxygen.nl/download.html

Navigate to project directory

```ssh
doxygen Doxyfile
python3 -m http.server 8000 --directory docs/dox/html/
```

Go to  `localhost:8000`  on browser.
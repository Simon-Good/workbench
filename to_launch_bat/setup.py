from distutils.core import setup
import py2exe
 
t1 = dict(script="script.py",
          dest_base="script",
          uac_info="requireAdministrator")
 
console = [t1]
 
setup(
    version = "1.0.0",
    description = "executable with privileges",
    name = "py2exe executable",
    console = console,
    )

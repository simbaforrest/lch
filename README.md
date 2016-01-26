Lighweight CPP Helper
=====================
LCH (Lightweight CPP Helper) is a collection of lightweight CPP Helper functions or classes, implemented in header files as either inline functions or template classes/functions, for easier CPP programming.

Author
------
Chen Feng <simbaforrest at gmail dot com>

Version
-------
1.0

License
-------
BSD

Installation
------------
Add the lch/include folder to your CPP compiler's include paths (e.g., using -I) and in your code add the following:

```
#include "lch.hpp"
```

or you can choose to only include the helper headers you need, e.g.:

```
#include "config.hpp"
```

and you should be able to use all helper functions. LCH is designed NOT to depend on any other CPP libraries except for the CPP STL, which is why it is "lightweight".

The helper headers/functions almost all comes with comments and thus are self-explanatory.
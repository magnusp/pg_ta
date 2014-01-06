HUGE DISCLAIMER!!!
==================
Do not under any circumstances use this in anything remotely close to a
production environment. Do not for a second think that this is, in any
way, stable code. It is a pet project, experimental, a prototype and/or
a proof of concept for calling functions from 
[TA-Lib](http://ta-lib.org/). I barely got it working during the winter
holidays of 2013.


pg_ta
=====
See test.sql for an example. Only function implemented at the moment is
MA/SMA (and with a hard coded order of 5).
I am aiming for something in the lines of what the python wrapper for
[TA-Lib](http://ta-lib.org/) is doing for all functions applicable
within the context of a postgres function(s).

To build it, just do this:

    make && sudo make install

I build/test it with:
    
    make clean; make && make installcheck && make install && \
     (clear; psql -U postgres -f test.sql)
 
 
Dependencies
------------
You need to have [TA-Lib](http://ta-lib.org/) compiled and installed
where the compiler will find it.


Copyright and License
---------------------

Copyright (c) 2014, Magnus Persson
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
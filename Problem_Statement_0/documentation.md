# 📝 Solution Documentation 

---

## Problem Understanding
**What the problem is asking:** PS-0 want us to create a simple calculator with basic arithematic functions, Trig functions , inverse trig functions and exponential related functions using our preferred language

**Key concepts involved:** 
- Dividing functions into a piecewise function for different types of inputs
- Approximating functions using Taylor polynomials
- Trignometric identities 
**My approach:** 

- The arithematic functions were implemented directily, except the divide function which checks if the denominator is zero and then prints a error message
- The next set of functions all lead towards creating a general a^b function. I used the identity a^b = e^(b*lna) . The first function i implemented was an int\_power function which uses a loop to calculate integral powers. Next i implemented a factorial function using recursion. A exponential function using the taylor series. Since the series is most accurate near 0, i separated the integral and fractional part of the argument, used the int\_power function for the integral part and taylor series for the fractional part . The ln function was tricky as it was non analytic and so only valid for x belongs to (0,2] . So i used x = 2^p * m , now i only need to find ln m using taylor series and can use a loop to find p. Finally all this build up was so i could write a general a^b function, i broke the function into a piecewise function for different types of inputs. Also i implemented some other related functions like log\_2, log\_10 , log\_a , sqrt
- Added some simple functions like floor, ceil, absolute value
- For the Trig functions i only need to implement the sine function from scratch as i can use identities for the remaining trig functions. First i wrote a sine function from 0 to 2pi by breaking it into 3 intervals and used 3 series for more accurate results. Then for the general sine function, used the identity sinx = sinx  +- 2npi to reduce it to principle branch
- The inverse Trig function was tricky as the taylor series converges very slowly near x = +-1, so i used taylor series for |x|<0.5 and a identity for 0.5<|x|<=1. The remaining inverse trig functions were implemented using identities, also since the taylor series used nCr , i also added the nCr and nPr functions to my calculator
- The ui, i used a variable called oper and a switch statement. The program first print a complete list of functions and then call the calc function indefinitely unless 0 is given as oper

---


##  Conceptual Learning

### **New Concepts I Discovered**
- **[NaN]:** [NaN or not a number - I learned how it is implement (0.0/0.0). It is useful for indicating failure]
- **[MinMax Polynomials]:** [These are polynomials different from the taylor series but which provide very accurate approximations for a small range with much less terms, though i didnt used it here ]
- **[Non Analytic Functions]:** [There are some functions like ln(1+x) and arctan x which regardless of how many terms don't approach the function outside a particular range]
- **[Error calculations]**[Used desmos to check how much error is in the functions i implemented]

## Challenges i faced and what i did 
- Orignally i thought that a^b = e^b*lna would be sufficient for all cases, but it isn't for cases like 0^-1, 0^0 etc. Finally i had to break it into many cases, even then I wasn't able to implement one particular case i.e negative nubers raised to (1/odd) power.
- datatype limitation the largest datatype long long is of 64 bits even then it can only store a maximum of 65 factorial
- Orignally i used a single taylor series centered at x = pi , but the error was sizable which would scale even more in the tangent and secant functions
- Orignally i was using Taylor series for arcsin x which would give a managable 6% error at x = 1, but this error quickly scale in arctan function. Finally i found an identity, which allowed me to use the series for |x|<0.5 and the identity for the remaining inputs
- Orignally i wanted a typing ui where the user would type sin(21) or exp(4.4,1.1), but i couldn't do it and decided to use a switch case instead




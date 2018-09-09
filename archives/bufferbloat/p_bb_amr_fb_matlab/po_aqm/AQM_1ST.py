# This code is for Active Queueing Managment, Author Amr Radwan, Inje University, Novemebr 2014
# for the paper: A joint Queue Management Scheme using Multi-Objective Parametric Optimization
# Authors: Hoang Linh To, Amr Radwan  Won Joo Hwang 
import numpy
from numpy import *
from numpy.numarray import array, zeros, dot, Float64, sqrt
from numpy import arange, cos, pi
from numpy import array, zeros,linspace,ones,exp
from numpy.linalg import norm
eps = input('eps= ')
t_segment=input('t_segment= ')
iteration=input('number of iterations= ')
t0=input('t0 = ')
tf=input('tf = ')
t=linspace(t0,tf,t_segment)
alpha_weight =input('alpha_weight= ')
w_star = input('w_star= ')
d = input('d= ')
S = input('S= ')
C = input('C= ')
u=ones((t_segment))    # Control function
x=zeros((t_segment,2))  # State functions
x[0] = array([0.0, 0.0])            # should given for AQM
psi=zeros((t_segment,2))  # Adjoint function
psi[-1]=array([0.0,0.0])           # for AQM
beta = 10
sigma= 10**-1
c=.0001
JJ=[10]
alpha_alpha=[1]
grad_J=[10]
h=(tf-t0)/(t_segment-1.0)

# Integrate Forward in time by Euler
def integrate1(F,t,u,x):
    def euler_step(F,tk,uk,xk,h):
        return h * F(tk,uk,xk)

    for k in range(len(t)-1):
        hh=1.0
        
        x[k+1] = x[k] + euler_step(F,t[k],u[k],x[k],hh)
    return x ,t
# Integrate Backward by Euler method
def integrate(G,t,u,x,psi):
    
    def euler_step(G,tk,uk,xk,psik,h):
        return h * G(tk,uk,xk,psik)

    for k in range(len(t)-2, -1, -1):
        hh=1.0
        psi[k]=psi[k+1] + euler_step(G,t[k+1],u[k+1],x[k+1],psi[k+1],hh)
    return psi,t

# This calculates the jacobian by using finite differences
# partial f_i / partial x_j = (f_i(x+e_j h) - f_i(x)) / h , h=1e-5---here h is e
def jacobian(f,t, control,x):
        e = 1.0e-5 
        n = len(control)
        jac = zeros ((n,n), dtype=Float64 )
        f0 = f(t,control,x)
        for i in range(n):
            temp = control[i]
            control[i] = temp + e
            f1 = f(t,control,x)
            control[i] = temp
            jac[:, i] = (f1 - f0)/e
        return jac
# Backtracking Line Search
def backtracking_linesearch(g,u,s):
		
		def q(alpha):
			if abs(alpha) < 1e-8 : # should be replaced with an almost equal check!!
				return 1
			return (Cost(t,u+alpha*s,x) - Cost(t,u,x))/(alpha * dot(g,s))

		alpha = 1.
		
                def q_test():
                    aa = 1e-2
                    for k in range(6):
                        aa=aa/10
                    aa=-aa
                    for k in range(6):
                        aa=aa*10
                
                #q_test()
                
                sigma=0.10
		while q(alpha) >= 1-sigma:
			alpha = alpha * 2
		# backtracking
		i = 0
                qa = q(alpha)
		while qa < sigma and i < 500:
                        alpha_plus = alpha / ( 2.* ( 1- qa))
                        alpha = max(1./beta * alpha, alpha_plus)
			i+=1
                        qa = q(alpha)
		return alpha
# The state equations
def stateEq(t,u,x):
    dx =  zeros((2))
    a=1.0/(d*d)
    b=x[0]*x[0]
    c=b/2.0
    A=1.0 - u
    l=A * S* x[0]
    dx[0]=  a - c * S * u
    dx[1]=  l - C
    return dx
# The adjoint equations
def adjointEq(t,u,x,psi):
    dpsi=zeros((2))
    a=1.0 - alpha_weight
    b=u * S * a
    c=x[0]* S * u * psi[0]
    A=psi[1] * u * S
    l=2.0*alpha_weight
    dpsi[0] =  b - c - A
    dpsi[1] =  l * (x[1] - w_star)
    return dpsi
# derivative of the Hamiltonian w.r.to the control
def pH(t,u,x,psi):
    du = 0*u
    for k in range(len(u)):
        cof1 = (1.0 - alpha_weight)
        cof2 = (-x[k,0]*x[k,0]*0.5*S)
        cof3 = (-S*x[k,0])
        du[k] = cof1 * S * x[k,0] + psi[k,0]*cof2+psi[k,1]*cof3
    return du
# The Functional 
def Cost(t,u,x):
    integrate1(stateEq,t,u,x)
    A=2.0
    l = 0.5
    return (tf-t0)/(t_segment-1.0)*(alpha_weight*((x2-w_star)*(x2-w_star)).sum() + (1.0 - alpha_weight) * u*(S*x1).sum())

#  Main Loop
for i in range(iteration):
    integrate1(stateEq,t,u,x)
    x1=x[:,0]
    x2=x[:,1]
    integrate(adjointEq,t,u,x,psi)
    J=Cost(t,u,x)
    JJ.append(J)
    dH=pH(t,u,x,psi)
    finite_differences= jacobian(Cost,t, u,x)
    g=finite_differences[0]
    s=-g              #search direction
    if abs(norm(g))<eps:
        print i,'&', J,'&',alpha,'&',norm(g),'&', dot(g,s),'\ \\hline'
        break
    else:
        u_old= u*1.0
        alpha = max(1.0,backtracking_linesearch(g,u,s))
        u=u_old +alpha*s #-alpha*dH
        alpha_alpha.append(alpha)
        print i,'&', J,'&',backtracking_linesearch(g,u,s),'&',norm(g),'&', dot(g,s),'\ \\hline'
        grad_J.append(norm(g))

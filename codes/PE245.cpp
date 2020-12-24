// http://www.hdml.gr/pdfs/journals/544.pdf
// if n = prod(q_i^{a_i}) with q odd primes, q_1 < ... < q_k, and n - 1 = h * (n - phi(n)) then
// 1. n is odd and square_free
// 2. h is even
// 3. q_k > kh

#include <bits/stdc++.h>
using namespace std;

long long N;

// Composite unit resilience from 2*10^9 to 10^11 encoded in base 62
string ans = "2bpoFN,2c8JIj,2cdDY1,2d4XMd,2dGXLn,2eIcqh,2f4PSZ,2fwtYr,2g8cPB,2g9HQz,2gI2e1,2hiXQr,2io38z,2jsPa1,2jY5Tp,2kiJMH,2kGEMJ,2kLCC9,2lb7yR,2loh7h,2luEPh,2lz7Ht,2mXaB7,2n72V9,2nMrrN,2pEiXh,2qRMkn,2r9gIN,2rs9GB,2rT2Lp,2sXwfb,2uBew1,2vLKmB,2wnBgV,2y2169,2y8DlH,2A4VWL,2ANzzN,2BvFo1,2BBuuf,2C7wgN,2CoAIf,2E0pGH,2E5Yrj,2FUV0V,2Go8Wz,2GTZ2t,2HtpMl,2HyL5V,2HAr8j,2ItC9B,2J8XFR,2Je06n,2JPqtx,2JRZcB,2KpUIf,2KIujb,2KTwxp,2LashV,2LoEN1,2MmqxF,2MCK2f,2PGkHt,2PTVeV,2QSmDp,2SuZ9F,2UfQzR,2UPIjV,2W6FEB,2WiCK1,2WBCg5,2WOqOd,2X9Orn,2XOTtH,2XZza1,2YGj6b,307n11,319g7f,31ia1l,31pfGp,32eHFR,32fYtZ,32CY01,32DTJ1,33wOID,33J04h,34c3N7,35d8O9,35MVeZ,35PDnT,36wttD,36NHf1,37BXn1,38f4hJ,39VbWV,3aWbMn,3bUG89,3cADij,3e1b01,3ecYyx,3eAqZj,3eEO91,3eLVDZ,3eMvA1,3fCKSt,3h4o5n,3hWqer,3iPXJn,3jpc1b,3jzhSf,3kd735,3klP0z,3l25Nn,3lboOF,3lPdLz,3mZZP9,3nT0Fz,3o2vtT,3ovOi9,3pl4IN,3pZTMr,3qPeDV,3qPOFF,3rd63h,3rvMqN,3sel5N,3twKXz,3ugGpf,3uL6tL,3vgcqV,3vy3dL,3w1Ew7,3wbBXh,3wgH0b,3wmsh1,3wyKWV,3ymaOz,3ySP71,3zfo6t,3zOc6H,3zTSvB,3AALax,3B2qdH,3D2eXx,3DqrS9,3FG1jL,3G67i9,3GwMCX,3GBWwV,3GF8DT,3HemoZ,3IjY6r,3IojXJ,3IpVLh,3IK0L5,3J70WH,3JqnpL,3JDDhx,3JFaz5,3JKqOF,3JZqOR,3K5Dz1,3LBToL,3LPpJp,3MaCeL,3Mxtml,3NcPjj,3NSUfZ,3OI5JX,3Qrvd3,3QHI8H,3TMWUp,3U96un,3Uixct,3UJVuF,3V2upN,3VMtyl,3WvDbP,3XSA7r,3ZdLYR,40Rv71,41eSuJ,41Aqoh,41PVuN,41V5O1,43nSEn,44fTw5,465rn3,478bTR,4a4eRt,4at5P1,4c4b7t,4c4SRz,4cP8pj,4d9c5f,4dbDSD,4e41AP,4esys1,4f5TAD,4f8cHF,4fIwj3,4gChod,4gHWo1,4hwTkP,4hxbxB,4jBXBd,4jOKzd,4kXuLj,4l495X,4l6Blj,4lb7X5,4lIFkN,4mVu31,4nEgLL,4oIj3P,4oLnpP,4rLBGD,4uccIj,4v3Qzz,4wFKuj,4xn6wx,4xsmAh,4zkSVR,4zPbTF,4zQWXh,4zSWe1,4AjQUH,4BUjOd,4CcGEH,4CUGOp,4Dw79V,4E3RWV,4Ebda3,4EcZTd,4EpAar,4EIw29,4F5ouX,4Fk9Wr,4FSVEd,4Gs3A3,4GFfc3,4H7OtL,4H98p9,4HrR79,4IkRV9,4JeVgh,4N0ezZ,4Nd3Wr,4NucFJ,4PIB8b,4PUdVl,4PZo5X,4QhZAt,4RaxO9,4RpVP1,4TjaaR,4UXP3z,4VdtHR,4VighP,4Vy5hf,4XhpLf,4ZE7up,4ZOZT9,50y4g1,50LoQx,51gBKx,53YY0D,54zOw1,55tDcV,56tFkL,57l79H,57J8mp,57UIXN,58dn55,590N8Z,5b1dOV,5bpUZT,5bx8J5,5dZNqH,5fkz85,5hQOFR,5ileM1,5jFmi3,5jUHkX,5kybA3,5lsEhz,5m6gJT,5nrmZH,5oyEqn,5oHqYh,5p8NuV,5qwQBx,5qGASH,5qQ0pf,5rgK0x,5rBLMt,5s0P8j,5voRFh,5wbFR9,5wyN9p,5x3eiT,5x3YKT,5yJlWV,5yT5fT,5AkkqR,5Exvsh,5F3db5,5HTL01,5IkWAz,5Iyo81,5IDvzh,5JKEBT,5KtAtl,5KHITz,5LiRr5,5Mjxz9,5MjyjH,5MVjMn,5NAGax,5Opvx1,5OVpAl,5PI77t,5QcV13,5QhYJZ,5QK9zL,5SC3lh,5SI3x5,5T7bIx,5TEh4h,5UirJZ,5UncsT,5UzwHR,5X5wtP,5Xqbaz,5YqmjR,5YUGzB,5ZLRxL,60fBil,60IrUL,62ZYaT,68PySN,69rxe9,69scRp,6a5sKF,6amupb,6amZAf,6aUIlP,6aYAm1,6cO4gD,6d41rr,6dE9ud,6ebsa1,6eUPLf,6eWMVV,6ft3ox,6fC89T,6gwPYz,6gBXLT,6gHKUn,6hWowX,6iAuJZ,6kIMPH,6kNdEl,6lRZxb,6m5Vs3,6moMg7,6mwPAF,6mBfxZ,6mHJwr,6n06n1,6nHnjz,6ojqUR,6piVnh,6qOUbB,6tNzan,6u7BhD,6ugaA7,6vnaLV,6wS8Ot,6zXf6H,6Ak67d,6AMdmN,6CMeo3,6Fozs1,6GiaNH,6GqWmD,6JTJg9,6MDufB,6N8tuP,6Nj8kj,6OylOn,6Px9gh,6PG4qF,6PHM6F,6PI4xF,6QjPvL,6R59hx,6RBapr,6RUN47,6TvUCN,6TvVHL,6TH5IB,6TLEx7,6V9ZUL,6VarYX,6VwDpp,6WsRDL,6X1A6D,6XgACt,6XXCo5,6YkQon,6YroL9,70uqdT,70IG0d,71Iwu1,74mdr7,7508e3,7554pb,75fP1Z,75uyDX,774Bc1,77Keof,78MvBV,79ci6t,7adtWZ,7alun3,7aCp0R,7aU215,7csN21,7d3yIt,7eijU1,7etj31,7fniP7,7fqfzf,7fUmY3,7gZczT,7h8Vzj,7iv2hV,7iJo8T,7k7Z5n,7l0vcj,7lRY89,7mc75X,7mtBtB,7mz1Q3,7mDhL1,7mPC5p,7nzfAn,7q8uwd,7qeV6t,7qZ4wt,7riNr7,7rzMrZ,7s0v5b,7uLh79,7vJ8Tr,7xlAJz,7yb4h1,7yvC41,7B18k5,7CA7lF,7CPaOj,7DP9Bf,7GU9eD,7Hcq0z,7He73F,7HvzN1,7I1B03,7Lx4R1,7LQvpZ,7NTm0d,7ORMej,7PnneT,7Q0FjP,7QYI27,7QZb09,7RxYQ1,7SU9wr,7Ts1wP,7Tx35r,7VjD8h,7VPf9X,7W20w5,7WWS9t,7X3V41,7ZyQYH,80dkqN,80y8ar,80KYgz,81l25b,83iVth,83r4w1,83rydf,85iGvF,86iNzN,87dbi1,8ak3kf,8bEHVd,8bKrYb,8cefbN,8cozkl,8dTGDP,8eadCP,8gx2wX,8idRj9,8iIJw1,8jnO81,8kTRB1,8qb8AH,8qF89Z,8tXezD,8AIZhr,8C2zQn,8CCNSz,8DyrpX,8DS0a1,8JecFj,8JL7U9,8JU06L,8OQkd1,8P0i6l,8Ppwt1,8PtbjZ,8Q7pwT,8QJ2fV,8SmUCp,8T1HLH,8T9vFr,8Ti6UH,8Wmpk7,8YYPcr,90mGzT,91MSlJ,92mo2L,92GYw1,930k4V,931Uzt,93N88z,94dDxd,9512w3,954CY7,97ey83,97sdJJ,97ymCb,9881Qj,98wwch,98Lm5F,9aL20V,9bqYaX,9f8CBn,9g0nU9,9gp0CV,9gqY9b,9hIP61,9hOHnR,9i4ge9,9jWFSb,9mjFGt,9mKQ8L,9qxPe1,9raFEd,9rtMhn,9rKSlR,9rRbYd,9sZ0Eh,9trV2B,9uG8mV,9uLxlf,9vj8Vt,9vMzwr,9wZpQf,9xq8J7,9BMlhb,9EjlZR,9Eroxf,9G1pA1,9GrUkB,9GBD6L,9H48TD,9IbPKz,9Ilogx,9IsIC9,9IxADn,9Lt2I1,9MYeYh,9NZX8T,9PgfBr,9PiG89,9Q0HHJ,9Q4jK1,9UAu1J,9Varsr,9VZsi1,9Xghl1,9XGaUD,9Zs9PF,a0xHSd,a0LheN,a1YYY1,a2nYKD,a3cSeH,a41EV1,a4jYqH,a4k3sZ,a5RT6T,a62SpF,a7pcWP,a9HE4P,aaZeuf,abBSpt,acGkj1,ahJ0qn,ai8697,amvxKr,amKXEB,aoEved,aqhmnf,arayvl,as1fhZ,aswCFf,atL7id,awqumr,awQZzt,axwb87,aAHG41,aBXRWX,aC6jh7,aCEACf,aDQeZb,aEWvmb,aFwSPR,aFCEX9,aGl7A7,aHNunZ,aKmMp3,aN1Ntr,aNNU9D,aO3p1J,aOsiTh,aPL3A1,aVGyi1,aX9hfp,aZdUr9,aZsZGH,b0yzm9,b1tgv1,b1BZF7,b2JPpF,b4IdJx,b6eNjL,b8Vy6r,b94YlN,bbsAw1,bbNZU3,bcl7Sz,bcZG3H,bdAWZX,beHVsx,beRVTN,bfCdl1,bgi55z,bj3zXF,bjPyNX,bkmQ01,bmwXhj,boJN5j,bqfIxb,brZPAT,bsiOaB,btHczH,btHxFT,butFQZ,buy33N,buPNfz,bwhQrt,byswoT,bytuHt,bzi6M7,bzZfvr,bAFu6z,bCEyLD,bDlhyR,bEJ1dt,bGFtFX,bH4gJF,bJaRtj,bJtp0d,bMSbL3,bN8DuT,bO0vYr,bOTVvV,bQG7Y1,bRoelb,bSgN7B,bSD0B1,bSW8bj,bUrfCr,bVMNwN,bWaq7t,bWG3LZ,bWZf3x,bXg20P,bZuKEX,bZXZkR,c2ZXe3,c3EH9B,c3ELa7,c3RIWz,c4XPwZ,c7e3fb,c8RXL1,cgHflT,chgtlZ,cjFAWP,ck3V0n,ckLKQZ,coWkLz,cql74h,cqJNY1,crZT7F,ct76K1,cttbzB,cuI4Fd,cwXQgd,cx889d,cxf0NL,cxyDin,cyfXVd,cBF7wl,cEITmF,cHMkh9,cIr02N,cIXHA9,cJobON,cNlOex,cPXZL1,cQIP7V,cREsw1,cScc5V,cTko1D,cTpvXb,cVK6dD,cWatQ9,cWJ73h,cX9XFt,cZo5rT,d0gUeJ,d0OQJf,d10A5l,d1OHJh,d2OQvF,d51FcL,d5rTnH,d6LszF,d70UX1,d9rrVt,datudB,daxr37,dbybh1,dbIsCV,ddKpXl,ddNAjx,deyZLF,deOEkP,dfpO0p,dgzXr1,dgHNV1,dgX0v1,dhN8IZ,dibYmL,dmpvQR,dmvE61,dnfZNf,dplJIl,dqLjcH,drr9pP,dsimfr,dsyG9t,dtBcHb,dtRSSX,dtW0Y7,dvjArt,dxCIHD,dxFmad,dDgDTN,dE6Q1d,dGzGt3,dIrTjJ,dIs5PL,dKaFbn,dKttIx,dKvg7t,dM59Aj,dMrsyb,dNdh33,dNCbrZ,dNDJvt,dSnTAl,dSxHI3,dU4N41,dVS2y1,dXb9Zl,dXcyjr,dZNkJr,e1U7s1,e6tgU9,e7kndD,e7ngD3,e7W7oF,e8aheh,ea454t,eaZjH3,ebgirt,ecb1Ur,ecJkLf,ehtXFP,ekexdZ,emRv6P,en0HsH,enO5n9,eoS7T9,eqOZ6n,eqTQyF,er9MlV,erc7pV,ey4E9t,ezibzH,eALqsN,eAV16b,eBD2ZT,eCvPwp,eDe2ZH,eDech7,eEDBpF,eFvr87,eG5Zyz,eIJOSF,eINGk1,eM90eb,eN6wu9,ePjSk9,ePQ9A1,eQIizJ,eT2jF5,eUpzTp,eVYxap,eY9P41,eYCtY3,eZ1o41,f0RJLt,f18V6L,f2ia2r,f3efe5,f3EZmn,f4ocxV,f6iE3J,f7zaxd,f7TuoB,f8M9p9,f9bR7t,f9jzUF,fcHXyH,fgK8jV,fjWMQh,flnpO1,flFGN1,fmkCfr,fmkTjR,fmnfRN,fmJ54h,fnmUeV,fnN5Eh,frMTil,fsGgqZ,ftd9W7,fudq25,fvj2F1,fwerNF,fxoUTJ,fyKXRp,fzqAkr,fAGH99,fCsqJ1,fF12q9,fFdNTf,fFVx0h,fGacFp,fIhVDT,fNadA3,fNPzSB,fQbNcH,fQX9oX,fRdcf9,fRsogR,fVxwCj,fZJkWX,g0Twhf,g1ZBlZ,g3opHn,g9y1Zr,gcSEc1,gdp8m1,gfMGhd,ghG1mJ,giMdb3,gmyg2r,gny1Bd,gof3I1,gpuRDt,gpFlSf,gsEgMd,gubI21,guic1P,guxwFR,guWfth,gvOjUd,gySKcx,gA1I01,gAobOL,gBdENn,gF9Uw3,gGZYy1,gHBUp1,gHZ4t9,gMgz67,gMXTgT,gOiRtJ,gOD7lh,gOPNUd,gPMTTz,gQiSBn,gSjd19,gUpGf1,gVp8DB,gVBYL5,gX3mbH,gYGGpJ,gZayjz,gZVJsh,h3PKUp,h5QLGl,h66VK1,h73yRJ,h8jzK1,h8rHrx,hdHZlt,hel03N,hgvRY7,hj5pTp,hkvhE1,hkApy1,hl3ZTx,hlG3NH,hncP0N,hnH3ft,hpxhxJ,hpHhRP,hrmBD9,hszMGZ,ht9IcF,huM49z,huORXn,hxwckB,hy05dN,hzI9Q1,hAO8j1,hBB64p,hCmSih,hCWBT5,hD3Uhr,hIBcrL,hICKpx,hLlt8d,hMJgPt,hPB7qh,hRUylt,hSoFw9,hV8DW9,hWDAtT,hY6hTF,i3zLD1,i3EZwV,i52Lb1,i57jPR,i6B3mr,iaA0zX,ibVZHF,idWBbX,ieO60N,ifLG5h,ih1NNx,ihWvpx,ij6tEL,ij9727,ilEOoV,imc1nH,imAscL,iqgQLp,irdRs1,isq1iT,itgq3d,itqx8V,iwPYCB,iA6TvN,iCV9Dh,iGgMjr,iHqPpx,iKTSNR,iLvped,iMtt23,iQfwMj,iQGScx,iQTKWN,iTQtu5,iTSz5P,iVkmEl,iWrZqT,iXcbS9,iY4z1d,iYlGbJ,iZEuSt,j1uztT,j4yudV,j5945T,j69ugD,j9R7Uh,jahS7d,jauFxR,jk818J,jkacc1,jmUxRF,joPvU3,jpUwJd,jqd4RX,jqeQtf,js0xn3,jsGCXB,jtaMA1,judNnH,juAxxL,juGxmP,jvv70F,jxj0fl,jycvhn,jANrmN,jBszNT,jEKGuz,jFs0J1,jHsbjT,jI2r3h,jLN4eR,jMLZlJ,jObUox,jPb82j,jQaYk1,jRHrG1,jU8oA5,jUFrb1,jYLPo1,k0pHUR,k0wa23,k10AFp,k1kYOP,k2IWAz,k46VrX,k4Hrul,k5omwh,k5EeLL,k6900J,k86RbZ,k9MrVr,k9NSi1,kaL1G3,kbFyxb,kdSFK7,kecqe7,keBxO1,kjI8Vb,kmv76F,kmAAiL,knh3v1,ktipFt,kuGjfX,kvJlTr,kwx0OP,kyJ8p7,kAh1kP,kFcTKj,kFBrR1,kFK4Y1,kHmTw1,kKz9GH,kNn7OR,kNylNd,kRNnkz,kVl5UV,kWcisD,kZ49UR,l06cHh,l5xBUf,l7GOnP,l9eHF1,laGh5x,lgftCP,lgBDU9,lhFnWl,liKHA1,ljkQER,ll5Mdp,loegkT,lsaXxX,luYoHt,lwHWJn,lxuZsZ,lyRgZR,lyVMK1,lzDJBD,lATNmz,lBsWg1,lBECSh,lDsphJ,lDTxUj,lEM4VR,lFSJ9n,lG9CVF,lGyRxf,lH7vzb,lHT5Wr,lNfkMT,lNphF1,lPMP1R,lX9z5t,lXuWuZ,lZ02zP,m2s8d3,m4ANa7,m5TP7t,m6mrv1,m8IROz,m9DTv5,makRAT,mc4aX1,mcqJzr,mdsM4f,mdICq9,mfY1fZ,mgAd0P,mlIgrr,mmmnJ3,mmtxIb,mnZTjj,mrT6sT,mtA1sx,mupJSV,mwR6fL,mzJCX3,mA3zr3,mABJ0J,mC9Uij,mGRNxV,mHsFPD,mKfIep,mMnNUL,mMoTyh,mNbHF7,mNcmp1,mO6OyL,mQB5P3,mUEjhh,mV8kwH,mXZqGR,n2k4xt,n2P43l,n5LUcZ,n6FFCX,n8IZ5Z,ncGEpr,neEmJd,nivddN,niMWZ1,niQLmV,nl5fpD,nmgrvH,nmWSYl,nqekQb,nr1mEB,nrfVBd,nsmi9P,nvquQR,nwhwuj,nBdNlt,nBD4T5,nC3VEn,nCBbsZ,nDxGCR,nFlfRV,nFo46D,nFXwEh,nJeatP,nKvpct,nMAYjB,nOkzJ7,nOkXPp,nW4JFt,nXQ6Mh,o0B41X,o2Fwk1,o3tx4H,o49V5F,o6li67,o7QB5L,o9wVQB,o9JenN,oa2voT,odNEuJ,of21w1,oibvz1,on6in7,opnIr9,oqc6px,oqBCQh,ovASv1,oxwIXP,oC1uzL,oCm5r1,oEfi5h,oEiKId,oH1nQP,oIwKYl,oIZz1t,oLOeaJ,oM5sWx,oM6cbV,oNmWUL,oNwQPZ,oOn84f,oQvpLL,oRsq0N,oTCDuR,oUcJNP,oW3SBB,p0e0ZX,p1Fu5z,pc3ZDZ,pcZjO1,pcZzmn,pdnRt9,pgWoBV,phbsFV,piPHhr,plMAIj,pnisW9,ppBMV5,ppK3Z9,prtG1t,prylE1,ps2HSn,pt0UwP,pwrhgn,pywy7r,pzQFO1,pBPBnz,pG7Kvx,pGu2yN,pGOXNJ,pHBHFD,pIpS4F,pMFmUF,pS50E5,pUSjSh,pXWyCt,pZkXd3,q4kgF5,q7LWDr,q9cfKT,qaSAg9,qcQli1,qdcOGr,qdoFQ7,qdBtiZ,qkmn9D,qnHzj7,qvr475,qwi5RT,qxcAi3,qzq6qF,qAoTU7,qB421n,qIPt4P,qLNkbF,qPeS3F,qQGNIx,qTG1Lr,qXMPYT,r1Ib11,r1OIlx,r2Nysr,r41fA1,r4ABTf,r8aMzt,r8tdgT,r93gQB,rgRIFb,rhFfHL,rlURVp,rmvPn9,rnBNw1,rnRI4D,ro0eYR,row2fN,rrqEML,rvzpEh,rwnaD3,rAY8TV,rC7EFB,rGWIEZ,rIYb2R,rJ4n1j,rLqHjH,rMarq1,rMR74P,rNfSZ1,rNIqd1,rNYLoT,rPDVd5,rPTr3t,rUbL35,rViXZ3,rXzN0D,rXKzdL,s44kwF,s5W7WH,s6qwjr,s8BfJ7,sdgcn1,sg6nLT,spvVyx,subsad,swF40B,sAAFX5,sAHUNX,sBeAv1,sD9SuX,sE8AQp,sLXqhR,sPGAvV,sQRT19,sSiI8F,sSSypF,sUlL6B,sUHnrF,sVOQul,sWubyJ,sWRqNX,sYxMSL,t3gTqz,t3paSJ,t6GAd1,t76bkX,tapOgF,taK76L,tci3B7,thybaT,tkp34D,tmT05L,trKjjZ,ts3BEb,ttbe61,tuIpSN,tvowW7,tvEQFN,ty7VMr,tzsVuh,tBhx3H,tBwRkd,tD9FsR,tDshSX,tEiNBh,tFaylN,tHvMWN,tJDwUV,tJIKAT,tJVitL,tLNHEt,tT4tFx,tVa7c9,u7uVuD,u7ScN1,ubhjTd,ubSfvl,ucxr9T,udHlvt,uixAXr,unumCV,upKmth,uqOaSV,utNnf1,uwQzR9,uzgSjZ,uCrIW1,uEp4Zd,uHXS51,uKknNZ,uKsS5l,uMsc0t,uMwqEF,uOhumL,uPTIEp,uYlJNh,uYNBi1,uZZxvF,v0dHBD,v0p9lr,v3XHJ3,v6aFMj,v9SFNZ,vb0LWb,vdON5p,veH0Qh,viXhJX,vnsjeR,voVpjh,vvGspd,vwGPxV,vxlqCR,vEPSCV,vMP71F,vOWvJV,vSd1jl,vVSCZ1,vWh0lx,vWu6w9,w1MWTz,w33oRb,w6bLi9,w7CR8Z,wabeWJ,wjfz8L,wlBJaz,wqtZv9,wqCfX5,wrHRHD,wrX2jN,wzYuFJ,wBADCT,wC7WPp,wCiHpp,wCvo4J,wCTxT3,wE564F,wKswTX,wL3eVR,wNNtMj,wOMQWN,wQK6YD,wR1ZUx,wSEfD1,wWlYrL,wWKeLV,wYyja7,wYUnJJ,x1actD,x1Pz31,x6qAtX,x7Su5b,x9WjBX,xaPjcL,xb6icz,xcNa23,xfKw71,xgd9KL,xhga51,xihUV1,xj9SqF,xrMceP,xs06Xz,xsiHnp,xwBPpd,xyuZJz,xzlLwn,xAXJQ1,xFcnzh,xFQSQ1,xIITpp,xJHsV1,xNQco7,xUBUdR,xVEKD1,xYVwMF,y6MLOz,y99n6D,y9nylV,yb9Sxf,yfBLtx,ygiUh1,ygkKoz,yi9AjD,yk1oDZ,yltZ6J,ymsngT,yojlnz,ysVnar,yvaWUx,yzzTKL,yLnlun,yMaV8F,yRXquJ,ySV0w1,yY1sF1,yZDTBB,yZGl31,z3j5in,z6y97t,z6A5R3,z8ZvUl,zcMMmN,zeYOMF,zj5RND,zkhCWR,zl63r3,zm8RU1,zrgAx1,zrvgj1,ztFAPl,zwABnt,zycxe7,zDE8UH,zG3Jp7,zIhXNt,zJnDFB,zK7ud1,zKzFfF,zLXWg9,zMadZN,zUc0BR,zVjie9,zY2rQx,A1wpXP,A1B9TR,Adkq9V,AdS4C7,Af1llL,An2V5r,AnmawZ,ApB5q1,ApSsbZ,As8Onb,Asx8q9,AvvTTB,AxzSRX,AzMgvX,AB6oHT,ABf38t,AD5QZx,ADw479,ARnESD,ARBn89,ARZZ49,ATfvuR,AUtqbZ,B5ggGx,B8FoXH,BazdeH,BaVtZJ,BcLPuT,Bd4qNZ,BfBLA1,Bid5E5,Bm38jD,BmeCgt,Bt0MVD,BuutT1,BxJhfP,ByvtsT,Bzyb3h,BBaPRB,BCqW6d,BFxwgz,BJTTq1,BM3HzP,BOooQ7,BPA8MH,BPHjlz,BQPkL1,BTfF0F,BWp8tL,BX2i7l,BZ4yjn,BZiJWt,C4xuj9,C8kIh3,C8l07h,CbgFSf,CdP5p1,CiUkXb,CoFopf,CpoHJj,CpUx1F,CtYZCh,Cw1bS3,CJe4Vj,CJGWCB,CMP0QH,CPdMXf,CR2cm1,CSw9kN,CTbqb1,CXfsYD,CZwS45,D0s2Af,D24lI5,D8cYM5,D9d2Dl,DauCFl,Dd8SWD,DfqrMD,DiTt17,Dkj7fX,DkPHxT,DlldKT,DmdcAd,DncktX,DpoxB1,DpP4lh,DqJha1,DrMWuP,Ds5Q2P,DtoL3l,DzT2PH,DAuE8X,DAG6jt,DD9Zv1,DEstkH,DKtdbl,DLgk9Z,DOAlU1,DSoKZ1,DSTLNd,DUEejn,DXISJj,DYcOxX,E5dFL1,E5m2YR,E6qfID,E7H6NJ,E7TuW3,EagoSh,EgbEuL,EgkryN,EhGa2p,EkN5Tf,EmeBDL,En5kLb,Eny21r,EoUoDZ,Ep6LPt,EtO0iL,EyrUq1,ECcfCX,EE6jcl,EEtnnP,EH1IkX,EH2dqH,ELJ8i1,EMCb9R,ERGWRj,EY7Fx1,EYGuvx,F5t611,F61bgJ,F6BsPJ,F8JEq5,FcHqHP,FgPgJ1,Fl6v3z,Flkhi9,FmqxL9,FpUCwp,Fs1MTH,FstsZT,FtzkxT,FDngUV,FDS4Fp,FFrbBl,FIaSlt,FKBoIt,FLYGQ5,FNS4az,FOypoT,FVKBGV,G1rwEh,G3iR3t,G6OWAn,G7D11x,G8uZjh,G9hfnh,GaqA7P,GeSlun,GfD257,GibRVd,Gk03dJ,GkE33J,Gpkqof,Gthkp3,GvWIGh,GxiWW7,GAicjb,GUhQjT,GWBbit,GWM72N,H6lQG7,H7vV5B,H89kVN,H9Q65L,HegbXj,HePacF,HgmpSB,HkbYR1,HmsTr1,HmN9cn,HohaLt,HoAJUH,Hp21XB,HqIRp1,HsoPrB,HukYoj,Hv4cRT,Hv95kd,HwgglJ,HymPZJ,HAdC1F,HBwtPj,HCHVkx,HD8wh1,HIWtEr,HM6OvN,HNIYJJ,HPebep,HQfVxN,HRdt0X,HSKH5Z,HVaQiL,HVy2u1,HWbIr1,HXokxH,I4cw63,I8FQT9,IiqVXN,IkbAxx,IA2vUf,IBDldD,IC8Mh5,ICE36F,IE8vB1,IFOFlB,IGEiH5,IGFbTZ,IHFECb,IJwLSD,ILO5ab,INNrx9,IPJ1Ph,IWTC5D,J1x0s1,J20CwX,J21oPD,J3pTYd,J85QW7,J8se4R,JbizVx,Jc5yPL,JcqnqD,JiiDFP,JiCMZB,JjzmcT,JjEizl,JjGKwd,JmvhKP,JoycED,JrYcZX,Jt2UoX,JwWdt1,JxYJ53,JyIfSR,Jzbv9l,JAuOih,JDz1ML,JWBCXd,JXDPe1,JXW6KH,K3Nd21,K75AQ1,K9dzbf,KaQBld,KbzTS1,KdjrFp,KnX2sd,KpCEXB,KxWBSL,KDgHln,KF98r1,KFubPp,KIRVWf,KKmN2x,KLbfgx,KLthJf,KN1FCh,KOk3hH,L0Xc3D,L21eqL,L46pWX,Lc9oll,LeKwdB,LkdGdV,LmE9uJ,LoGMqX,LrLiYL,LspuZT,LvLf2P,Lw5BX1,LBMBOD,LFLSRb,LHeoOD,LHVJoR,LMZgPJ,LOqe8D,LYzKe3,M44RZf,M5cnmd,M5v0cJ,M5RTGx,M6izkZ,M7rpVt,M9vMk1,MekDLl,MgNI1f,MiUsoF,MkoLsT,MoTFTN,Mp37Jn,Mv0lUt,MvjhXj,MyX1Kz,MzfylB,MzEsbN,MC0EfH,MCqCEx,MDNtPP,MEUFFn,MGRRWb,MI6jBF,MKYGTN,MO60dl,MOYf9R,MPu7o3,MSnxRX,MV88PT,MWcwb3,N2ygWN,N7psYN,N8iLpX,N8RmwJ,Nd46ft,NdAYNt,NfxEPB,NfJYc5,Nhvo9p,NhRrFp,Nivevz,NnW5lX,NpwT0L,NGI3OV,NH1UXn,NJxGON,NMFTZH,NNAvV3,NTnzUf,NVUEJ3,O5cM4z,O8DGyF,Oa4qJ1,OfHdjp,OiFL2F,OkXLmn,OlxiAD,Open6n,OqKXkR,OAGKfL,OC7461,ODf1h1,ON3mtx,ONFYFJ,OOxzn1,OSp6Dd,OTcGrz,OYnczB,OYVSHN,P3D3vb,P3WqsN,PdljKJ,PdPG1Z,PkmTzd,Po50B1,Pqnh3n,PrVBiV,PvqvN5,PzleFn,PAcu1h,PCfFsB,PCPh9f,PFPxZr,PJmwOz,PROaVJ,PV4jkD,PWRP7f,PXGmBh,PZ0nUJ,PZ5MId,Q02OWV,Q0W105,Q1Pjmd,Qblq4F,QbHtXj,QbXW75,Qd7G7x,QeGs35,QjtM2F,QlLNfV,QnzTsX,Qo2igF,Qqv1ET,QvfJ1z,QxflIj,QB8xQp,QCjlsn,QHnBhT,QP03f5,QPzLuX,QTcbX7,QZkUer,R1V5a1,R20k8H,R9vgEB,RbDNgZ,RcUVR1,Rkpliz,RmUmqF,RoXkOX,RsjNmP,RtoWFR,RAtfnd,RBeU21,RDa961,RGIwu3,RGTjGD,RHar0f,RIU8qf,RJMraH,RMmFjr,RQqNJr,RTkqMz,RYbonp,RYs001,S9YVPN,Sbfltn,SftDhF,SkyacL,SqLkuF,SuioZb,Sv2Hyt,SOAMtH,SOZf7B,SPjabJ,SPzbYj,SQHFkj,T1BvTb,T2vur7,T3Hjj3,T4mzBT,T6xBan,T9yBI1,TbHOin,TprNzL,TpF4dx,TqWv2z,Ts7c3t,TswnUx,TtCEJ1,TuLSVd,TyH2oJ,TAXVRf,TCvcpn,TEwcjN,TGd5dX,TMvKLH,U4JDN3,U6yXUd,U8N0h1,U9MWvJ,Ub0e0L,UbSiyb,UdmPlJ,UffpLB,UlSExF,UmFlSH,Uomrh3,Upozz5,UvujXJ,UwPCOp,UCUYA9,UKYSxb,UL7fYt,UO0xz3,UUvwH1,UUBZ01,UUV5CN,UXPOrt,V64YzZ,V8j0Df,V9r1DP,VagBg1,Vbhr15,VhmKWf,VhwPU9,Via1KR,Vk0fDb,VkSvex,VlbqTz,VlSZzz,VoozAh,VrdPUZ,VtDzQp,VtZMTH,VvNl4h,VwRNgH,VDzFkJ,VGODwR,VI0bSV,VI94P1,VJcZfx,VJFryj,VPA9f7,VQLYe7,VTFq2F,VVD6sn,VYToUZ,W0a4O1,W0IWtF,W11JC1,W1AlaX,W3WD6l,W6YhYx,WdGVwV,WnSfZ1,WruMU1,WsvCBj,WsXufr,WwmRgx,WxoV81,WxCil7,WxVwuD,WAIWH7,WEGzBx,WKi33H,WNwNXZ,WQeZUB,WQhPp1,WR2psb,WSWsbd,WUPnWz,X1xtil,X1FRNJ,X1WowR,X2kBED,X32YAh,XbAPer,XbR8YN,Xh4pRx,XhjG0F,Xr3ttx,XwAMuN,XybmcD,XyxN2x,XAfDzb,XEJ1b3,XMAlwh,XSeaRV,XU92Tf,XVnb6l,XVZPjR,XYJvt1,XYXOZN,XZ1Wpx,Y2IxjL,Y5j5hJ,Y7VmdP,YaGDbn,YfjNsn,Yfx061,YjCUJr,Ym29vl,YpJEjD,Yr0yh5,Ysxe3d,YwfzM3,YwmnZL,YH5ayF,YHY84z,YIUBpj,YRbQiP,YRbUC1,YWojRB,Z0OkYL,Z2Ih0J,Z6v0E1,ZcykSd,ZfkcA1,ZfH50p,ZhPxXt,ZjhfVf,ZqsPrZ,ZurJKD,Zvzg2H,ZvOq91,ZxK6aB,ZxYzil,ZyhjDn,ZzyX6b,ZBeVv1,ZG63Bx,ZH2BUZ,ZH6t1f,ZKSWm1,ZLoyk7,ZMFl0T,ZR5OQT,ZSaAil,ZU2xTP,ZYnPNn,1016h1T,105tywH,10a8rVN,10cW58Z,10ftG7J,10g8whZ,10gaN1l,10j1X4b,10k8co3,10noHM9,10nCQlF,10nY0SN,10rqM95,10v154R,10wsImB,10yVWTF,10DNdO5,10FVUbB,10Lvej1,10OEVYL,10PqRW1,10PS3MV,10SGrZH,112kxJ1,118jdoh,11bIIuX,11cCG3r,11d8InF,11ioi1b,11sAe8f,11tGGrb,11IDDjP,11QamHj,11RGvzx,11YaQ7R,11Ybfeh,11ZAviL,1201lzh,120MPRZ,124OFjz,124Q7Sp,125J561,127SxVN,128loW7,12byZVf,12cenzB,12euoCR,12hho2p,12iWTxn,12ocvxd,12rGWhf,12ttkpB,12xedRR,12xXoGZ,12zB1WB,12BeWaJ,12Na5bR,130qxjf,136krQl,139WPoj,13dFUkB,13gs8Wn,13htMtR,13nKwG9,13sNB7V,13sWpeB,13vxrml,13xJDB1,13BEvfL,13CviUB,13Ef7hJ,13FpnbX,13FqZSb,13OrsOn,13W7SDP,13WysRp,1401nor,1412xtd,149SxZz,14bcX1N,14hymYR,14jCOzt,14pp84D,14pCUJr,14ud7rp,14wpvdx,14Ciq8R,14CI0G1,14EBj8b,14GWvdR,14Lg9Mf,14Ngk8B,150slYP,150Jpgn,150NJYP,152DH6L,154IsI1,154TUTz,155fdNJ,156SDLj,157iQXR,157TcL1,15cO4ol,15iKUc1,15jVL3F,15t2Ngt,15uqLPL,15xhYTX,15AVxQV,15HIPVV,15LdsN1,15NA4wn,15RZVl7,15TvMP5,15Ve37n,15VoY51,15WOr8z,15YMV87,163n6gf,166NPhV,16fjS7F,16ft327,16k0cBn,16nD21P,16oxb59,16qoqrh,16t6Odr,16uRKpn,16wAmQH,16xAkDN,16z8utz,16zetZz,16CoGBX,16GsWK1,16Sj3k9,16XfYx7,16XCeIJ,172cyPT,172GVp9,173P9PT,176UoYx,17cg53x,17dh2C5,17hb4Lb,17l0AMd,17nLXkd,17oc6CD,17s8zbh,17wwHoP,17xw0nX,17zO9rj,17Ecp4f,17GA1IF,17J92V5,17Mv6YF,17Oec0H,17RDshD,17SWBtf,17TwZf1,17VZ3Id,17WQIML,17YIa3F,183MYH3,1870rhj,187KkT1,18bR3SX,18ccFpN,18jhOJ1,18mQ9Rj,18qjg8n,18vs1Wt,18ybMXh,18zzH5r,18zXSZP,18DbFoL,18GdimN,18I1Vf7,18MSzxx,18NwO8P,18Oe43T,18QL02L,18RIdZX,18S4hh3,18VokFR,18Y2Wp1,1904YA1,190I48f,195Cyz1,195URuN,1979hix,19aOXw1,19baFo3,19cNjff,19fm5Yb,19l0xd7,19nDFZl,19ogFhj,19rAqkP,19rWAhP,19tRp6z,19zSWpZ,19CWYUB,19GZXYt,19JTBFz,19N34VZ,19YYpXH,1a5THXd,1a6J3hl,1a8BMwR,1abNDdp,1acpRll,1ad3rTN,1aekTK1,1agaZ5R,1agjdCb,1akbRKJ,1anJmKh,1axE6w1,1az70bX,1aAdrT9,1aDoLrX,1aKxmtH,1aLkoGd,1aLUyrx,1aQPJrP,1aREdXj,1b06Os7,1b16Yf1,1b42Cmb,1b9wDOD,1baZZhD,1bc4p43,1beED01,1bfuXFL,1bl5Yrp,1bzrFyh,1bHyF2L,1bIJaOZ,1bIR7DZ,1bJOINP,1bPNPPP,1cdt11H,1cdTx6l,1cexX49,1ceF5Hz,1ceYBFt,1ck9KmZ,1ckCkmR,1cnjShT,1cAbpbr,1cClsX5,1cFBqJJ,1cFVN1H,1cIm6O1,1cNdAzF,1cOesej,1cRs8fV,1cTAdYH,1cX93jz,1d07VaV,1d4Vi39,1d6GnE3,1dgTO13,1dp2lcL,1dqQHYR,1dubqqD,1dvqBNF,1dzCCFN,1dAiZ39,1dCz2mP,1dD8971,1dFjCaL,1dFzfXJ,1dLCG83,1eikq8Z,1ejh26T,1ekS5dL,1eBbQSF,1eFvqHf,1eGH2u1,1eIWMwx,1eJCfJd,1ePFpHZ,1eXlANT,1f2cOUp,1f99wdX,1fdj2o1,1fgf6bT,1fiiF59,1fiZb6b,1fjczad,1fjO3qJ,1fmjnBL,1frRptl,1fsXv9J,1fCMtt1,1fMUdwV,1g2rUD3,1g4E6vR,1g5YXcJ,1gbjJ11,1gfJDtV,1ghWV7N,1gnc7nf,1gt2QGD,1gx6ktj,1gIGQFJ,1gJvYcR,1gV7DGz,1gXMmhl,1gYQbgH,1hbF3eZ,1hk2PhN,1hmCzqJ,1hs7X1d,1htrMP9,1hvG9CV,1hyB0CB,1hAcvud,1hAjMKB,1hDkEP9,1hIL0Tx,1hJLcC3,1hKgQUl,1hNpf21,1hWC0HZ,1i1t9DT,1i21BpX,1i5fb3X,1ic3jp9,1ieRXY7,1imrwlx,1ios4Q1,1irdDpL,1iuoMhR,1iyg4w7,1izMZv1,1iAGaBJ,1iAHFbZ,1iBFJKX,1iFqOfp,1iGuUw3,1iKz301,1iQc9PF,1iULSXz,1j0wVtR,1j6uB5z,1j7zGvV,1j7O299,1j92Yj1,1jauYJf,1jjHNxr,1jmtUu3,1jotPEN,1jtyCL9,1jxyCOR,1jCHwmh,1jH8Vit,1jYmElB,1jYMTdN,1k63yiH,1k8nwN1,1kcPEPB,1khrT73,1ki9ngH,1kkHwyV,1kmGD2f,1kw5nSJ,1kzn3LH,1kKmgi1,1kKSRHl,1kQiibJ,1l4mU15,1l7RUMh,1l9kqIh,1l9ZbNr,1lgzDhD,1ljX0bx,1lAWXvx,1lCrz51,1lIQtP9,1lMdr3B,1lMKXW9,1lNk7lD,1lOXFnx,1lQsaEV,1lRclcH,1lS9xwF,1lTxVmV,1lV8kPf,1lVE1bz,1lZNK0t,1m2V8jB,1m4da5L,1m8IaY3,1mbkRML,1mp9UlT,1mt7RCP,1mDcQUb,1mHbBoZ,1mNcMZj,1mR9lI1,1mVdgk3,1mXPGc5,1n1i0Eb,1n69Mq7,1n7hbNb,1nbUcQJ,1njyiEN,1nnUMLT,1noI6QL,1nv5kVB,1nzyFVh,1nBoBVx,1nKjp1t,1nRZP4F,1nSgJK7,1nSjOaF,1nXrvJh,1o5BOLL,1o938Cl,1oaY1an,1og41Gt,1ol3TK9,1ooK42h,1opSO4j,1otBnt5,1oyCpjH,1oC5R8D,1oDX4q3,1oGd4ZT,1oNKtOx,1p4oyw1,1p7cVZT,1phSeOz,1phZDad,1ps0nup,1psIJRZ,1psUqRb,1pzDN6j,1pBOQnP,1pCBQOp,1pGfr89,1pIrAPb,1pJ1GO1,1pMzuBZ,1pNKzJz,1pQzvo1,1pRQMv1,1pS6EVV,1pVyyMj,1pWaZxf,1q12pF1,1q2QXvJ,1qdb1k1,1qj0WVJ,1qjh6zt,1qlB52D,1qoEhgF,1qpJxWL,1qv2avD,1qzqEAT,1qEmrLN,1qH9Wol,1qTt0oJ,1qVzFh1,1r0fohb,1r22mz7,1rbmtWp,1rfEWHZ,1rgZkmF,1rhCJG3,1rireJH,1rlR8zh,1rsBncj,1rFKZab,1rHVzEj,1rJAx9x,1rQZir3,1rUAUbN,1rW27jd,1rYZfhr,1s3fFH9,1s5ruYb,1segtm5,1sfrq81,1slulCP,1snic3z,1srhnOV,1stvIX3,1sxej13,1sClivr,1sPXZxt,1t1Q5xD,1t4u00d,1taABkX,1tjPgKN,1toPeDD,1tvmFPr,1twYA6l,1tJnjAD,1tN6dpZ,1tYcDSh,1u27lS5,1ui1YaL,1uis5tH,1uiPovp,1unCowb,1unUTR1,1urH93Z,1uDew25,1uDgh81,1uGdyZN,1uLFr99,1uO6vS9,1uUukMR,1uXmRVD,1uXJu8J,1uYqSgl,1v1NPB5,1v1QqAL,1v4FVSn,1v4Stxp,1v5cHM1,1vAUBmV,1vBmy8F,1vHgQEd,1vTrWB3,1vTxR9N,1vVpqFz,1vXa7qj,1wd2TB3,1wtwPkp,1wx3sqf,1wCF1S7,1wUJEzT,1wWKSF7,1xeCfO5,1xf4sW1,1xj5yW1,1xjtjWj,1xlEw73,1xsZb2f,1xv7PZZ,1xwz9Zj,1xxtvN5,1xAWpjZ,1xAXSKr,1xC1YSL,1xMRQ4b,1xOPxFJ,1xTGyS7,1y0Nv5J,1y2gt3p,1y6x2R7,1ykgAg1,1yteaWp,1yupZsh,1yAIzXJ,1yBadqF,1yBP7L7,1yCQdu5,1yHl0N1,1yKacOV,1yTVEO1,1yU8iHF,1yXn97R,1z0cFtb,1z3R4Ln,1z7Gsir,1zaMJSd,1zb1K1T,1zcAmsn,1zcX6kJ,1ze4tPX,1zfoHfj,1zfKxj1,1zi9dC9,1zjMJQb,1zurU1Z,1zwpmMl,1zBnniZ,1zCADE1,1zGwCbT,1zRi04p,1zVEi6r,1zWSsfV,1A5ALAz,1A5CQuF,1A5S9TL,1A7mPX5,1AeWdnf,1AhyA1l,1ApvcAx,1Aqn19z,1As2BRL,1Au29I1,1AFR8b9,1AKE1XH,1ARPpHT,1AVeDdJ,1AYXx2T,1B0V3a5,1B1G5AN,1B8YecJ,1Bgtupx,1Blz4G5,1BpHC9z,1BrRQCN,1BwWqwr,1BCwIJn,1BIlmMN,1BMUHy3,1BP5FhP,1BVeFpz,1C0M9sJ,1C7hPQ1,1Ccup91,1CqTpnX,1CtMvaD,1CvsXtz,1CvXP8z,1Cxn7lJ,1CCiOS1,1CE5k5r,1CNMUkT,1CONItH,1CSRIIN,1CToR8B,1CVCnqH,1CWBCfx,1CYYdFx,1D5zpbd,1D5Rw8l,1DdWk23,1Dg0YcX,1DofbzV,1DsjBJF,1DslDyD,1DFbGgd,1DLhTFB,1DU837T,1E8k1aZ,1E9KOzF,1EoAefb,1Err8xn,1EtBdz1,1EylXK5,1EChsyj,1EIeTif,1EN5Qt3,1EQuBCH,1ESCUod,1EX6GhT,1F9MOYV,1Fc8fZX,1FgbK4f,1FgY3sX,1Fmsxz7,1Fnj2NJ,1FwD6oJ,1FxA0tN,1FCeHoH,1FFC6rh,1FGOfZt,1FQkxFL,1FU1cZh,1FVI73J,1G0QkMh,1G2Uo3x,1G9yDf1,1Gkdhl9,1GmN0BH,1Gq6kdJ,1GqIL1z,1GtE8MD,1GvUISh,1GBYfKr,1GN9kYJ,1GNRHxV,1GOnrPD,1GQ2Kd1,1GZ3im9,1H0WF11,1H83I3r,1H90It1,1HaZkun,1HiRi2z,1Hlviq1,1Ho5jtp,1Ht2NE1,1HzQAif,1HRt3r1,1HUeCsx,1I1Z9Ph,1I8OUJx,1I9i8QT,1IbBI8T,1IgeJzF,1IiZWPL,1Isy8Ih,1IuQZGz,1IzsBbn,1IC9Np3,1IEMHOz,1IGDprB,1IInK75,1IL1MtV,1IMO1VD,1ITRDvB,1IUyN4H,1IYmcPD,1J1Vw6V,1J8o0tJ,1JglFwb,1JgTFjF,1JkNpKb,1Jli87b,1JpYvZL,1Juyoo7,1JuCRdH,1JGe4lB,1JHMkgN,1JR5ZMF,1JSnT31,1K0e8d5,1K0y89D,1K31QP1,1K3kLE5,1K9eOjn,1K9lqmP,1KfuXiX,1KlwCCP,1KyaVf1,1KFD67D,1KHaZa1,1KKxtrZ,1KLjNml,1KMoe05,1KMy3ob,1KSeOCf,1KSQRwh,1KUP2qn,1L2bwPx,1L4RoCX,";

namespace CompositeUnitCoresilience {

/* A few composite unit coresilience:
15 85 255 259 391 589 1111 3193 4171 4369
*/

long long N;

const int MAX_PRIME = 1600000;
bool is_prime[MAX_PRIME];
vector<int> primes;

void sieve() {
  memset(is_prime, true, sizeof is_prime);
  is_prime[0] = is_prime[1] = false;

  for (int i = 2; i < MAX_PRIME; ++i) {
    if (!is_prime[i]) continue;
    primes.push_back(i);
    for (int j = i*2; j < MAX_PRIME; j += i) {
      is_prime[j] = false;
    }
  }
}

// Output the sum by adding one more prime
long long sum(int k, long long n, long long phi) {
  // np-1 = h(np - phi(p-1))
  // np-1 = h*n*p - h*phi*p + h*phi
  // p(n + h*phi - h*n) = h*phi + 1

  int p = primes[k];

  long long num = n*p - 1, det = n*p - phi*(p-1);

  long long h = num / det;
  if (num % det) h += 1;

  long long ret = 0;
  for (h += (h & 1); (det = n + h*(phi-n)) > 0; h += 2) {
    num = h*phi + 1;
    long long p = num / det;
    if (n * p > N) break;
    if (num % det != 0) continue;

    if (is_prime[p] && (n*p - 1) % (n*p - phi*(p-1)) == 0) {
      ret += n * p;
    }
  }

  return ret;
}

// Output the sum of unit coresilience
long long dfs(int k, long long n=1, long long phi=1) {
  if (1LL * n * primes[k] * primes[k+1] > N) return 0LL;
  int p = primes[k];

  return dfs(k+1, n, phi) + dfs(k+1, n*p, phi*(p-1)) + sum(k+1, n*p, phi*(p-1));
}

long long run(long long _N) {
  N = _N;
  sieve();
  return dfs(0);
}

}

__int128 sum_prime(long long n) {
  int sn;
  vector<long long> n_div_i;

  for (long long i = 1; i*i <= n; ++i) {
    n_div_i.push_back(n / i);
  }
  sn = n_div_i.size(); // sqrt(n)
  for (int i = n_div_i.back() - 1; i > 0; --i) {
    n_div_i.push_back(i);
  }
  __int128 dp[n_div_i.size()];

  for (int i = 0; i < n_div_i.size(); ++i) {
    dp[i] = (__int128) (n_div_i[i] + 2) * (n_div_i[i] - 1) >> 1;
  }

  for (int p = 2; p <= sn; ++p) {
    if (dp[n_div_i.size() - p] > dp[n_div_i.size() - p + 1]) {
      long long p2 = 1LL * p * p;

      __int128 sp = dp[n_div_i.size() - p + 1]; // the sum up to p-1

      // "Sieve" the prime p for all dp
      for (int j = 0; j < n_div_i.size(); ++j) {
        if (n_div_i[j] < p2) break;

        // Actually try to find dp that stores 1 .. n_div_i[j] / p
        long long idx = n_div_i[j] / p;
        idx = (idx <= sn ? n_div_i.size() - idx : (j+1) * p - 1);

        dp[j] -= (dp[idx] - sp) * p;
      }
    }
  }

  return dp[0];
}

ostream &operator << (ostream &o, __int128 num) {
  if (num == 0) {
    o << 0;
    return o;
  }
  vector<int> v;
  while (num > 0) {
    v.push_back(num % 10);
    num /= 10;
  }
  for (int i = (int) v.size() - 1; i >= 0; --i) {
    o << v[i];
  }
  return o;
}


int main() {
  clock_t t = clock();
  cerr << sum_prime(269) << endl;
  cin >> N;
  if (N > 2000000000) {
    long long sum = 0;
    long long cur = 0;
    for (char c: ans) {
      if (c == ',') {
        if (cur > N) break;
        sum += cur;
        cur = 0;
        continue;
      }

      cur *= 62;
      if ('0' <= c && c <= '9') cur += c - '0';
      else if ('a' <= c && c <= 'z') cur += c - 'a' + 10;
      else cur += c - 'A' + 10 + 26;
    }
    cout << sum + 430130354248LL + sum_prime(N) << endl;
  } else {
    cout << sum_prime(N) + CompositeUnitCoresilience::run(N) << endl;
  }
  cerr << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
  return 0;
}

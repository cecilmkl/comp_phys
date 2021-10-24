# Plot of 2 particles and their motion in xy-plane with and without particle interactions
import numpy as np
import matplotlib.pyplot as plt

# pi:   0: no interactions, 1:interactions

data0 = np.loadtxt('./Results/RK4_i_10000_d_100_p_2_pi_0_outputs_xy_pert_0_rs_0_f_0.0_w_v_0.0.txt', skiprows=1)

data1 = np.loadtxt('./Results/RK4_i_10000_d_100_p_2_pi_1_outputs_xy_pert_0_rs_0_f_0.0_w_v_0.0.txt', skiprows=1)


# No interactions: $axis $interaction $particle
x01 = np.array(data0[:,0])
y01 = np.array(data0[:,1])
x02 = np.array(data0[:,2])
y02 = np.array(data0[:,3])

# Interactions: $axis $interaction $particle
x11 = np.array(data1[:,0])
y11 = np.array(data1[:,1])
x12 = np.array(data1[:,2])
y12 = np.array(data1[:,3])


fig, axes = plt.subplots(1,2)#, figsize=(7, 7)) # default:6.4, 4.8 sharex = True, sharey=True
fig.suptitle('Motion in xy-plane w/ and w/o particle interactions') # remove later?
#fig.set_size()

# Plotting no interaction vs interaction:

axes[0].plot(x01,y01,label='Particle 1')
axes[0].plot(x02,y02,label='Particle 2')

axes[1].plot(x11,y11,label='Particle 1')
axes[1].plot(x12,y12,label='Particle 2')


for ax in axes:
    ax.set_xlim([-10**4, 10**4])
    ax.set_ylim([-10**4, 10**4])
    ax.add_patch(plt.Circle((0, 0), 10**4, linestyle="--", color='grey', fill=False)) # for penningtrap circle
    ax.grid()

axes[0].set(xlabel = 'x', ylabel='y', title='No interaction')
axes[1].set(xlabel = 'x', title = 'Interaction')
#plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)#plt.legend()

#plt.legend(bbox_to_anchor=(1.05, 1), loc='best') # x,y position

plt.legend(loc='best')
plt.savefig('./Figures/xy.pdf')
plt.show()

You may use icecream/icecc to spread compilation across as many hosts as are avaliable in your LAN (only), with icecream daemon running. On all your slave hosts install:

```bash
sudo apt install icecc
```

On your GUI machine additionally install an optional monitor and execute it:

```bash
sudo apt install icecc icecc-monitor
icemon &
```

On one of the slaves, which acts as a server, start the scheduler (Debian example):

```bash
sudo /etc/init.d/icecc-scheduler start
```

Your monitor should soon discover the hosts in your LAN. Please consult your distro's manual how to start a service (icecc-scheduler) at startup. It's recommended to adjust the number of accepted jobs on each slave to the amount of RAM, and to the heat tolerance. For instance to make a low-end laptop accept just one job at a time, please alter the variable `ICECC_MAX_JOBS` to `"1"` in `/etc/icecc/icecc.conf`. The below command will automatically find and use icecream. Note however, that it's only possible to build a generic binary this way.

More icecream documentation on [Github](https://github.com/icecc/icecream), and [Mozilla.org](https://developer.mozilla.org/en-US/docs/Mozilla/Developer_guide/Using_Icecream).


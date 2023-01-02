# asio-tutorial
Using Boost Asio with modern C++. A brief high level introduction to boost asio.

These examples where tested with boost 1.75 on CentOS 8 (Rocky Linux)

One way to install this version of asio is

```
mkdir -p ~/src
cd ~/src
wget https://boostorg.jfrog.io/artifactory/main/release/1.75.0/source/boost_1_75_0.tar.gz
tar xf boost_1_75_0.tar.gz
cd boost_1_75_0
./bootstrap.sh \
  --libdir=/usr/lib64 \
  --with-libraries=system,thread,test,chrono,regex,date_time,filesystem,locale,random,atomic,log,program_options,exception
./b2 -j 8
sudo ./b2 install
```

If you want to try a newer version they can be found here:
https://boostorg.jfrog.io/artifactory/main/release/

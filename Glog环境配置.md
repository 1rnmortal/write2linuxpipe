### syslog-ng安装

```sudo yum install epel-release -y && sudo yum install syslog-ng -y```

### syslog-ng配置	

配置文件位置：```/etc/syslog-ng/syslog-ng.conf```

管道文件目录为```otherdata/log/```，请确保有这个文件夹例如```mkdir otherdata/log```

↓↓↓↓↓↓↓↓配置文件内容↓↓↓↓↓↓↓↓ **！！叹号包围的内容需要替换！！**

**最后一行log中指定的source必须在上文定义且指定文件**

```
@version:3.5
@include "scl.conf"

@module syslogformat
@module afsocket
@module affile
@module afprog
@module afuser
@module basicfuncs
@module dbparser
@define autoload-compiled-modules 1

  options {
      log_msg_size(671088640);
      flush_lines(2);
      log_fifo_size(1000000);
      time_reopen(10);
      use_dns(no);
      dns_cache(yes);
      use_fqdn(yes);
      keep_hostname(yes);
      chain_hostnames(no);
      check_hostname(yes);
      create_dirs(yes);
      dir_perm(0755);
      perm(0644);
      stats_freq(1800);
      mark_freq(0);
      threaded(yes);
  };

  template log_format { template("$PROGRAM $MSG\n"); template_escape(no); };
  source s_log1 {
      pipe(！！！"#log1Dictionary"！！！);
  };

 source s_log2 {
      pipe(！！！"#log2Dictionary"！！！);
  };

  destination d_log_remote {tcp('#ip' port(#port) template(log_format));} ;
  log {source(s_log1);source(s_log2);destination(d_log_remote);flags(final);};
```
**↑↑↑↑↑↑↑↑**配置文件内容**↑↑↑↑↑↑↑↑**

**配置指导：**

- #log1Dictionary配置举例 ```/home/work/Server/otherdata/log/colorland_pipe.log```
- 上面的例子中有两个管道，根据需求调整管道个数，下面source(s_log1)的地方也需要同步修改
- ip/port是指向glog接受服务器,联系人 王思亮


启动命令：
```sudo syslog-ng -Fvde```

**注意事项：**
1. 确保libpipe.so放于GameServer.dll同级目录

2. 仅在linux 64位可用

3. 添加环境变量 glog值为open```export glog=open```

4. 启动服务器之前需要先启动syslog-ng，建议将syslog-ng设为开机启动或将启动命令加入启动脚本中


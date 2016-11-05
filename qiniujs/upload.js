var qiniu = require("qiniu");
var path= require("path");
var config = require('ini-config');

var filePath

if(process.argv.length != 4){
	console.log("faild")
	return;
}
else
  filePath = process.argv[2]

//上传到七牛后保存的文件名
var key = process.argv[3]

//需要填写你的 Access Key 和 Secret Key
qiniu.conf.ACCESS_KEY = config.qiniu.ak;
qiniu.conf.SECRET_KEY = config.qiniu.sk;

//要上传的空间
bucket = config.qiniu.bucket;


//构建上传策略函数
function uptoken(bucket, key) {
  var putPolicy = new qiniu.rs.PutPolicy(bucket+":"+key);
  return putPolicy.token();
}

//生成上传 Token
token = uptoken(bucket, key);

//构造上传函数
function uploadFile(uptoken, key, localFile) {
  var extra = new qiniu.io.PutExtra();
    qiniu.io.putFile(uptoken, key, localFile, extra, function(err, ret) {
      if(!err) {
        // 上传成功， 处理返回值
        console.log("success");       
      } else {
        // 上传失败， 处理返回代码
        console.log(err);
      }
  });
}

//调用uploadFile上传
uploadFile(token, key, filePath);

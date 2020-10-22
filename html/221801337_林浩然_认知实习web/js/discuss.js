var txt = document.getElementsByClassName('txt')[0];
var btn = document.getElementsByTagName('button')[0];
var pl = document.getElementsByClassName('pl')[0];
var Olen = document.getElementById('len');
var user= document.getElementsByClassName('Name')[0];
var oGender= document.getElementsByName('gender');

txt.onblur = function() {
    txt.style.width = '450px';
    txt.style.heigth = '150px'
}
txt.oninput = function() {
    Olen.innerHTML = txt.value.length;
}
btn.onclick = function() {
        var gender = "";
        for (var i=0;i<oGender.length;i++) {
           if (oGender[i].checked) {
              gender = oGender[i].value;
              break;
           }
      }
    if (txt.value == '') {
        confirm('你确定不输入内容吗')
        return false;
    } else if (user.value == '') {
        confirm('你确定不输入姓名吗')
        return false;
    }else if (gender == ""){
         confirm('你确定不输入性别吗')
        return false;
     }else {
        var ul = document.createElement('ul');
        pl.appendChild(ul);
        var li = document.createElement('li');
        ul.appendChild(li);
        li.innerHTML =txt.value+"&emsp;---"+ user.value+"("+gender+")";
        user.value='';
        txt.value = '';
        var li = document.createElement('li');
        ul.appendChild(li);
        var date = new Date();
        li.innerHTML = date.toLocaleDateString();
        var oa = document.createElement('a');
        li.appendChild(oa);
        oa.innerHTML = '删除';
        oa.style.float = 'right';
        oa.style.href = '#'
    }
    oa.onclick = function() {
        oa.parentNode.parentNode.remove()
        oa.style.cursor = 'pointer'
    }

}
!function(a,b){a.addEventListener("DOMContentLoaded",function(){(function c(){let a=b.querySelectorAll(".menu-item-has-children");a.forEach(a=>{let b=a.children[0];b.addEventListener("click",c=>{let b=a.children[1],d=b.scrollHeight;b.classList.contains("show")?(b.style.height="0px",b.classList.remove("show"),b.parentElement.classList.remove("show")):(b.style.height=d+"px",b.classList.add("show"),b.parentElement.classList.add("show")),c.preventDefault()})})})(),function d(){let c=b.querySelector(".current-menu-item"),a=c.parentElement;a.classList.contains("sub-menu")&&(a.classList.add("show"),a.parentElement.classList.add("show"),a.style.transition="unset",a.style.height=a.scrollHeight+"px",setTimeout(()=>{a.style.transition=""},600))}()})}(window,document)
class Node{
constructor(){
this.children={};
this.isEnd=false;
this.freq=0;
}
}

class Trie{
constructor(){
this.root=new Node();
}

insert(word){
let curr=this.root;
for(let ch of word){
if(!curr.children[ch]){
curr.children[ch]=new Node();
}
curr=curr.children[ch];
}
curr.isEnd=true;
}

increaseFrequency(word){
let curr=this.root;
for(let ch of word){
if(!curr.children[ch])return;
curr=curr.children[ch];
}
if(curr.isEnd)curr.freq++;
}

dfs(curr,word,res){
if(curr.isEnd){
res.push({word:word,freq:curr.freq});
}
let keys=Object.keys(curr.children).sort();
for(let ch of keys){
this.dfs(curr.children[ch],word+ch,res);
}
}

autocomplete(prefix){
let curr=this.root;
for(let ch of prefix){
if(!curr.children[ch])return[];
curr=curr.children[ch];
}
let res=[];
this.dfs(curr,prefix,res);
this.sortSuggestions(res);
return res;
}

wildcardDFS(curr,pattern,pos,word,res){
if(!curr)return;

if(pos===pattern.length){
if(curr.isEnd){
res.push({word:word,freq:curr.freq});
}
return;
}

let ch=pattern[pos];

if(ch==="?"){
let keys=Object.keys(curr.children).sort();
for(let key of keys){
this.wildcardDFS(curr.children[key],pattern,pos+1,word+key,res);
}
}
else{
if(!curr.children[ch])return;
this.wildcardDFS(curr.children[ch],pattern,pos+1,word+ch,res);
}
}

wildcardSearch(pattern){
let res=[];
this.wildcardDFS(this.root,pattern,0,"",res);
this.sortSuggestions(res);
return res;
}

sortSuggestions(res){
res.sort((a,b)=>{
if(a.freq===b.freq)return a.word.localeCompare(b.word);
return b.freq-a.freq;
});
}
}

const trie=new Trie();
const searchBox=document.getElementById("Mysearch");
const suggestionsList=document.getElementById("suggestions");

fetch("words.txt")
.then(response=>response.text())
.then(data=>{
let words=data.split("\n");
for(let word of words){
word=word.trim().toLowerCase();
if(word!==""){
trie.insert(word);
}
}
console.log("Words loaded successfully");
})
.catch(error=>{
console.log("Error loading words.txt",error);
});

searchBox.addEventListener("input",function(){
let text=searchBox.value.toLowerCase();
let parts=text.trim().split(" ");
let prefix=parts[parts.length-1];
showSuggestions(prefix);
});

function showSuggestions(prefix){
suggestionsList.innerHTML="";

if(prefix==="")return;

let suggestions;

if(prefix.includes("?")){
suggestions=trie.wildcardSearch(prefix);
}
else{
suggestions=trie.autocomplete(prefix);
}

if(suggestions.length===0){
let li=document.createElement("li");
li.textContent="No suggestions found";
suggestionsList.appendChild(li);
return;
}

for(let item of suggestions){
let li=document.createElement("li");
li.textContent=item.word;

li.addEventListener("click",function(){
let text=searchBox.value;
let parts=text.trim().split(" ");

parts[parts.length-1]=item.word;

searchBox.value=parts.join(" ")+" ";

trie.increaseFrequency(item.word);

suggestionsList.innerHTML="";
});

suggestionsList.appendChild(li);
}
}

const darkTheme=document.getElementById("dark");
const lightTheme=document.getElementById("light");

darkTheme.addEventListener("change",function(){
document.body.style.background="#121212";
document.body.style.color="white";
});

lightTheme.addEventListener("change",function(){
document.body.style.background="#f5f5f5";
document.body.style.color="black";
});
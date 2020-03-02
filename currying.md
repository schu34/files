# Currying in Javascript

## What is it?

Simply put, Currying is just the practice of making every function take exactly one input and produce one output. But wait, some functions need more than one argument to do their job. In fact we can even take a very simple example,  a function that adds 2 numbers:
```js
function add(a,b){
	return a + b
}

```

How can we possibly implement this functionality using only functions that accept one argument? You may want to take a second to try this yourself. The trick is to pass only the first argument to the `add` function, and thn return a second function which takes the second argument.

Somthing like this:

```js
function add(a){
	return function(b){
		return a+b
	}
}
```

Or the more concise version with arrow notation

```js
a=>b=>a+b;
```

We could use the function like this

```js
console.log(add(5)(6)) //11;
```

## So... Why?

Well theres a lot of good reasons to write our functions like this. For one thing, we could use our add function as an add function factory. Maybe we want a function to add 5 to a number. Easy:

```js
const add5 = add(5);
add5(6) //11
add5(3) //8
```
How does this work? Well add returns a function so instead of calling that function outright we just save a reference to it (that's our `add5` function)	
now we have a reusable way to add 5 to any number, without writing any extra code. This is pretty nice, but how often do you actually need to create an `add5` function? Not that often, but there's other times using a curried function as a function factory is really useful. The main example I use in my day-to-day is creating event handlers.

Let's say we have a component where the user selects a number from one to ten. When the user selects a number we want update some state, but also send a message to our server to track what number the user selected. One implementation might look like this:
```js
const NumberPicker = ({numbers})=>{
	const [selected, setSelected] = useState(null);

	return(
		<> 
		{numbers.map((num)=> <Number onClick={()=>{
		setSelected(num);
		reportToServer(num);
		//some other stuff we need to do when this number is clicked. 
	}}>)}
		</>
		); 
}
```

This implementation is fine, it's pretty easy to understand right now, but imagine if our application gets more complex, and we end up doing more and more inside our `onClick` handler. Having all that logic inside our `return` statement could get pretty messy after a while. If `onClick` was just a number or a string, then when it computing it inline became complicated, we'd just define a function we could call contain that logic. 

const firstName = "Linh"

const number = 33

const arr = [
    'string',
    33,
    function()
    {
        console.log('hello-world')
    }
]

// 33
//console.log(arr[1])

// hello-world
arr[2]()

for (let i = 0; i < arr.length; i++)
{
    console.log(arr[i])
}

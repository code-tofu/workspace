import CreateUser from '../features/user/CreateUser';
import { useSelector } from 'react-redux';
import Button from './Button';

function Home() {
  const username = useSelector((state) => state.user.username); //state.slice.varName
  //useSelector to get a variable from state

  return (
    <div className="my-10 px-4 text-center sm:my-16">'
      {console.log('Username',username)}
      <h1 className="mb-8  text-xl font-semibold md:text-3xl">
        The best pizza.
        <br />
        <span className="text-yellow-500">
          Straight out of the oven, straight to you.
        </span>
      </h1>
      {username === '' ? (
        <CreateUser />
      ) : (
        <Button to="/menu" type="primary">
          Continue Ordering, {username}
        </Button>
      )}
      {/* if button recieves to prop it is a react router link else it is a normal button - see Button.jsx */}
    </div>
  );
}

export default Home;

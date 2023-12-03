import Button from '../../ui/Button'
import { deleteItem } from './cartSlice';
import {useDispatch} from 'react-redux';

function DeleteItem({pizzaId}){
    const dispatch = useDispatch();
    return (
        //include pizza ID as payload
        <Button type="small" onClick={()=> dispatch(deleteItem(pizzaId))}>Delete</Button>
    )
}

export default DeleteItem;
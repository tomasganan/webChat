import { Component, OnInit } from '@angular/core';
import { ToastrService } from 'ngx-toastr';

export class Message {
  from: string;
  to: string;
  msj: string;
  receive: boolean;
}


@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})


export class LoginComponent implements OnInit{
  user: any;
  websocket;
  loginStatus: any;
  toContact: any;
  public contacts = [];
  message: any;
  messages: Message[] = [];
  constructor(private toastr: ToastrService) {
    this.websocket = new WebSocket('ws://127.0.0.1:9000',
      'dumb-increment-protocol');
  }

  login() {
    this.websocket.send('firstnamews:' + this.user);
    this.loginStatus = true;
  }
  receive() {
    const context = this;
    // tslint:disable-next-line:only-arrow-functions
    this.websocket.onmessage = function (message) {
      console.log(message.data);
      if (message.data.indexOf('Duplicate') === 0) {
        context.toastr.error('Error', 'Este nombre ya esta en uso');
        context.loginStatus = false;
        return;
      }
      if ( message.data.split(':')[0] === 'contact') {
        if (message.data.split(':')[1] !== context.user) {
          let exist = false;
          for(let i = 0; i <= context.contacts.length; i++) {
            if(context.contacts[i] == message.data.split(':')[1]) {
              exist = true;
            }
          }
          if(!exist) {
            context.contacts.push(message.data.split(':')[1]);
          }
        }
        return;
      }
      if ( message.data === 'reset') {
        context.contacts = [];
        return;
      }

      if ( message.data.split(':')[0] === 'from') {
        const msj = {
          msj: message.data.split(':')[2],
          from: message.data.split(':')[1],
          to: this.user,
          receive: true
        };
        context.toastr.info('Mensaje nuevo de: ' + message.data.split(':')[1]);
        context.messages.push(msj);
      }
    };
  }

  ngOnInit(): void {
    this.receive();
  }

  toMessage(c: any) {
    this.toContact = c;
  }

  sendMessage() {
    this.websocket.send('toContact:' + this.toContact + ':' + this.message );
    const msj = {
      msj: this.message,
      from: this.toContact,
      to: this.user,
      receive: false
    };
    this.messages.push(msj);
    this.message = "";
  }

  showToastr(){
    this.toastr.info('Mensaje nuevo de ' + this.toContact);
  }
}
